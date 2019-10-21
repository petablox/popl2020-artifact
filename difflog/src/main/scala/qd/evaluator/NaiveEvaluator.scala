package qd
package evaluator

import qd.instance.{Assignment, Config}
import qd.util.Timers

object NaiveEvaluator extends Evaluator {

  override val toString: String = "NaiveEvaluator"

  override def apply[T <: Value[T]](rules: Set[Rule], pos: Token => T, edb: Config[T])
                                   (implicit vs: Semiring[T]): Config[T] = {
    var state = State(rules, pos, edb, changed = true)
    while (state.changed) { state = immediateConsequence(state.nextEpoch) }
    state.config
  }

  case class State[T <: Value[T]](rules: Set[Rule], pos: Token => T, config: Config[T], changed: Boolean)
                                 (implicit val vs: Semiring[T]) {

    def addTuples(relation: Relation, newTuples: Seq[(DTuple, T)]): State[T] = {
      val oldInstance = config(relation)
      val newInstance = newTuples.foldLeft(oldInstance)(_ + _)
      val newConfig = Config(config.map + (relation -> newInstance))
      val newChanged = changed || newTuples.exists { case (tuple, value) => value > oldInstance(tuple) }
      State(rules, pos, newConfig, newChanged)
    }

    def nextEpoch: State[T] = if (!changed) this else State(rules, pos, config, changed = false)

  }

  def immediateConsequence[T <: Value[T]](state: State[T]): State[T] = {
    Timers("NaiveEvaluator.immediateConsequence(State)") {
      state.rules.foldLeft(state)((nextState, rule) => ruleConsequence(nextState, rule))
    }
  }

  def ruleConsequence[T <: Value[T]](state: State[T], rule: Rule): State[T] = {
    implicit val vs: Semiring[T] = state.vs

    var assignments = Vector(Assignment.Empty)
    var remainingLits = rule.body
    for (literal <- rule.body) {
      assignments = extendAssignments(literal, state.config, assignments)

      // Collapse assignments
      remainingLits = remainingLits.tail
      val relevantVars = remainingLits.map(_.variables).foldLeft(rule.head.variables)(_ ++ _)
      assignments = assignments.map(_.project(relevantVars))
      assignments = assignments.groupBy(_.map)
                               .map({ case (m, as) => Assignment(m, as.map(_.score).foldLeft(vs.Zero: T)(_ + _)) })
                               .toVector
    }

    val vrule = Value(rule.lineage, state.pos)
    val newTuples = assignments.map(_ * vrule).map(_.toTuple(rule.head))
    state.addTuples(rule.head.relation, newTuples)
  }

  def extendAssignments[T <: Value[T]](
                                        literal: Literal,
                                        config: Config[T],
                                        assignments: Vector[Assignment[T]]
                                      ): Vector[Assignment[T]] = {
    for (assignment <- assignments;
         f = assignment.toFilter(literal);
         (tuple, score) <- config(literal.relation).filter(f);
         newAssignment <- extendAssignment(literal, tuple, assignment))
    yield newAssignment * score
  }

  def extendAssignment[T <: Value[T]](
                                       literal: Literal,
                                       tuple: DTuple,
                                       assignment: Assignment[T]
                                     ): Option[Assignment[T]] = {
    var ans = assignment
    for ((par, field) <- literal.fields.zip(tuple)) {
      par match {
        case v @ Variable(_, _) =>
          if (!ans.contains(v)) ans = ans + (v -> field)
          else if (ans(v) != field) return None
        case Constant(c, _) => if (c != field) return None
      }
    }
    Some(ans)
  }

}
