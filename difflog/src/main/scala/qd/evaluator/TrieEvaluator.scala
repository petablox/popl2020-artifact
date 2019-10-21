package qd
package evaluator

import qd.instance.{Assignment, Config}
import qd.util.Timers

object TrieEvaluator extends Evaluator {

  override val toString: String = "TrieEvaluator"

  override def apply[T <: Value[T]](rules: Set[Rule], pos: Token => T, edb: Config[T])
                                   (implicit vs: Semiring[T]): Config[T] = {
    val trie = RuleTrie(rules)
    var state = State(trie, pos, edb, changed = true)
    while (state.changed) { state = immediateConsequence(state.nextEpoch) }
    state.config
  }

  case class State[T <: Value[T]](trie: RuleTrie, pos: Token => T, config: Config[T], changed: Boolean)
                                 (implicit val vs: Semiring[T]) {

    def addTuples(relation: Relation, newTuples: IndexedSeq[(DTuple, T)]): State[T] = {
      val oldInstance = config(relation)
      val newInstance = newTuples.foldLeft(oldInstance)(_ + _)
      val newConfig = Config(config.map + (relation -> newInstance))
      val newChanged = changed || newTuples.exists { case (tuple, value) => value > oldInstance(tuple) }
      State(trie, pos, newConfig, newChanged)
    }

    def nextEpoch: State[T] = if (!changed) this else State(trie, pos, config, changed = false)

  }

  def immediateConsequence[T <: Value[T]](state: State[T]): State[T] = {
    Timers("TrieEvaluator.immediateConsequence(State)") {
      implicit val vs: Semiring[T] = state.vs
      immediateConsequence(state, state.trie, Vector(Assignment.Empty()))
    }
  }

  // Applies a RuleTrie to a configuration
  def immediateConsequence[T <: Value[T]](
                                           state: State[T],
                                           trie: RuleTrie,
                                           assignments: Vector[Assignment[T]]
                                         ): State[T] = {
    // Step 0: Collapse assignments.
    // Elided because early experiments showed no reductions in number of assignments, and
    // caused a slow-down while computing immediate consequences
    /* val ax0 = assignments
    val ax1 = ax0.map(_.project(trie.variables))
    val ax2 = ax1.groupBy(_.map)
                 .map({ case (m, as) => Assignment(m, as.map(_.score).foldLeft(vs.Zero: T)(_ + _)) })
                 .toSeq */
    val ax2 = assignments

    var nextState = state

    // Step 1: Process sub-tries
    for ((literal, subTrie) <- trie.map) {
      val ax3 = extendAssignments(literal, nextState.config, ax2)
      nextState = immediateConsequence(nextState, subTrie, ax3)
    }

    // Step 2: Process leaves
    for (rule <- trie.leaves) {
      implicit val vs: Semiring[T] = state.vs
      val vrule = Value(rule.lineage, state.pos)
      val newTuples = ax2.map(_ * vrule).map(_.toTuple(rule.head))
      nextState = nextState.addTuples(rule.head.relation, newTuples)
    }

    nextState
  }

  def extendAssignments[T <: Value[T]](
                                        literal: Literal,
                                        config: Config[T],
                                        assignments: Vector[Assignment[T]]
                                      ): Vector[Assignment[T]] = Timers("TrieEvaluator.extendAssignments") {
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
