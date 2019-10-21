package qd
package evaluator

import qd.instance.{AssignmentTrie, Config}
import qd.util.Timers

object TrieJoinEvaluator extends Evaluator {

  override val toString: String = "TrieJoinEvaluator"

  override def apply[T <: Value[T]](rules: Set[Rule], pos: Token => T, edb: Config[T])
                                   (implicit vs: Semiring[T]): Config[T] = {

    implicit val ordering: Ordering[Variable] = new Ordering[Variable]() {
      val allVariables: Set[Variable] = rules.flatMap(_.variables)
      val maxOccurrences: Map[Variable, Int] = (for (v <- allVariables)
                                                yield v -> rules.map(_.body.map(_.fields.count(_ == v)).sum).max).toMap
      val varSequence: Vector[Variable] = allVariables.toVector.sortBy(v => -maxOccurrences(v))
      val variableIndex: Map[Variable, Int] = varSequence.zipWithIndex.toMap
      override def compare(x: Variable, y: Variable): Int = variableIndex(x).compare(variableIndex(y))
    }

    val trie = RuleTrie(rules)
    var state = State(trie, pos, edb, changed = true)
    while (state.changed) { state = immediateConsequence(state.nextEpoch) }
    state.config

  }

  case class State[T <: Value[T]](
                                   trie: RuleTrie,
                                   pos: Token => T,
                                   config: Config[T],
                                   changed: Boolean
                                 )(implicit val ordering: Ordering[Variable], implicit val vs: Semiring[T]) {

    private val _assignments = scala.collection.mutable.Map[Literal, AssignmentTrie[T]]()
    def assignments(literal: Literal): AssignmentTrie[T] = {
      if (!_assignments.contains(literal)) {
        val ans = AssignmentTrie(config(literal.relation).support, literal)
        _assignments.synchronized { _assignments(literal) = ans }
      }
      _assignments(literal)
    }

    def addTuples(relation: Relation, newTuples: IndexedSeq[(DTuple, T)]): State[T] = {
      val oldInstance = config(relation)
      val newInstance = Timers("TrieJoinEvaluator.State.addTuple.instanceIncrementTime") {
        oldInstance ++ newTuples
        // newTuples.foldLeft(oldInstance)(_ + _)
      }
      val newConfig = Config(config.map + (relation -> newInstance))

      val newChanged = changed || newTuples.exists { case (tuple, value) => value > oldInstance(tuple) }
      State(trie, pos, newConfig, newChanged)
    }

    def nextEpoch: State[T] = if (!changed) this else State(trie, pos, config, changed = false)

    override def toString: String = {
      val n = System.lineSeparator()
      val buffer = new StringBuilder()
      buffer.append(s"===$n")
      for (relation <- config.map.keys) {
        buffer.append(s"---$n")
        buffer.append(s"Relation $relation$n")
        buffer.append(s"  ${config(relation)}$n")
      }
      buffer.toString()
    }

  }

  def immediateConsequence[T <: Value[T]](state: State[T]): State[T] = {
    Timers("TrieJoinEvaluator.immediateConsequence(State)") {
      implicit val ordering: Ordering[Variable] = state.ordering
      implicit val vs: Semiring[T] = state.vs
      immediateConsequence(state, state.trie, AssignmentTrie())
    }
  }

  // Applies a RuleTrie to a configuration
  def immediateConsequence[T <: Value[T]](
                                           state: State[T],
                                           trie: RuleTrie,
                                           assignments: AssignmentTrie[T]
                                         ): State[T] = {
    implicit val ordering: Ordering[Variable] = state.ordering
    implicit val vs: Semiring[T] = state.vs

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
      val ax3 = AssignmentTrie.join(assignments, state.assignments(literal))
      nextState = immediateConsequence(nextState, subTrie, ax3)
    }

    // Step 2: Process leaves
    for (rule <- trie.leaves) {
      val ax3 = ax2 * Value(rule.lineage, state.pos)
      // We directly convert the AssignmentTrie ax3 into the set of output tuples using AssignmentTrie.toTuples(...).
      // An alternative is to extract the set of Assignments supporting ax3 using AssignmentTrie.support, and
      // subsequently use Assignment.toTuple(...) to convert it into the set of output tuples, as follows:
      // val newTuples = ax3.support.map(_.toTuple(rule.head))
      // Early experiments indicate that our present choice is faster.
      val newTuples = ax3.toTuples(rule.head)
      nextState = nextState.addTuples(rule.head.relation, newTuples)
    }

    nextState
  }

}
