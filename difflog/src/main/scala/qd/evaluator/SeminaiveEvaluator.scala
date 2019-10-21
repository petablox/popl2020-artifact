package qd
package evaluator

import qd.instance.{Assignment, Config}
import qd.util.{Contract, Timers}

object SeminaiveEvaluator extends Evaluator {

  override val toString: String = "SeminaiveEvaluator"

  override def apply[T <: Value[T]](rules: Set[Rule], pos: Token => T, edb: Config[T])
                                   (implicit vs: Semiring[T]): Config[T] = {
    var state = State(rules, pos, edb, Config(), edb)
    while (state.changed) { state = immediateConsequence(state.nextEpoch) }
    state.config
  }

  case class State[T <: Value[T]](
                                   rules: Set[Rule],
                                   pos: Token => T,
                                   config: Config[T],
                                   deltaCurr: Config[T],
                                   deltaNext: Config[T]
                                 )(implicit val vs: Semiring[T]) {

    val changed: Boolean = deltaCurr.nonEmptySupport || deltaNext.nonEmptySupport

    def addTuples(relation: Relation, newTuples: Seq[(DTuple, T)]): State[T] = {
      val oldInstance = config(relation)
      val newInstance = newTuples.foldLeft(oldInstance)(_ + _)
      val newConfig = Config(config.map + (relation -> newInstance))

      val deltaTuples = newTuples.filter { case (tuple, value) => value > oldInstance(tuple) }

      val dcr = deltaCurr(relation)
      val ndcr = deltaTuples.foldLeft(dcr)(_ + _)
      val newDeltaCurr = Config(deltaCurr.map + (relation -> ndcr))

      val dnr = deltaNext(relation)
      val ndnr = deltaTuples.foldLeft(dnr)(_ + _)
      val newDeltaNext = Config(deltaNext.map + (relation -> ndnr))

      val ans = State(rules, pos, newConfig, newDeltaCurr, newDeltaNext)
      Contract.assert(if (changed) ans.changed else true)
      ans
    }

    def nextEpoch: State[T] = if (!changed) this else State(rules, pos, config, deltaNext, Config())

  }

  def immediateConsequence[T <: Value[T]](state: State[T]): State[T] = {
    Timers("SeminaiveEvaluator.immediateConsequence(State)") {
      state.rules.foldLeft(state)((nextState, rule) => ruleConsequence(nextState, rule))
    }
  }

  def ruleConsequence[T <: Value[T]](state: State[T], rule: Rule): State[T] = {
    rule.body.foldLeft(state)((nextState, literal) => deltaConsequence(nextState, rule, literal))
  }

  def deltaConsequence[T <: Value[T]](state: State[T], rule: Rule, deltaLiteral: Literal): State[T] = {
    Contract.require(rule.body.contains(deltaLiteral))

    implicit val vs: Semiring[T] = state.vs

    var assignments = Vector(Assignment.Empty)
    var remainingLits = rule.body
    for (literal <- rule.body) {
      assignments = if (literal == deltaLiteral) extendAssignments(literal, state.deltaCurr, assignments)
                    else extendAssignments(literal, state.config, assignments)

      // Collapse assignments
      remainingLits = remainingLits.tail
      val relevantVars = remainingLits.foldLeft(rule.head.variables)(_ ++ _.variables)

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
