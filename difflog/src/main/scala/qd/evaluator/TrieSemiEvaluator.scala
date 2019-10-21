package qd
package evaluator

import qd.instance.{Assignment, Config}
import qd.util.Timers

object TrieSemiEvaluator extends Evaluator {

  override val toString: String = "TrieSemiEvaluator"

  override def apply[T <: Value[T]](rules: Set[Rule], pos: Token => T, edb: Config[T])
                                   (implicit vs: Semiring[T]): Config[T] = {
    val trie = RuleTrie(rules)
    var state = State(trie, pos, edb, Config(), edb)
    while (state.changed) { state = immediateConsequence(state.nextEpoch) }
    state.config
  }

  case class State[T <: Value[T]](
                                   trie: RuleTrie,
                                   pos: Token => T,
                                   config: Config[T],
                                   deltaCurr: Config[T],
                                   deltaNext: Config[T]
                                 )(implicit val vs: Semiring[T]) {

    def changed: Boolean = deltaCurr.nonEmptySupport || deltaNext.nonEmptySupport

    def addTuples(relation: Relation, newTuples: Seq[(DTuple, T)]): State[T] = {
      val oldInstance = config(relation)
      val ntp = newTuples.filter { case (tuple, value) => value > oldInstance(tuple) }

      val newInstance = ntp.foldLeft(oldInstance)(_ + _)
      val newConfig = Config(config.map + (relation -> newInstance))

      val oldDCInstance = deltaCurr(relation)
      val newDCInstance = ntp.foldLeft(oldDCInstance)(_ + _)
      val newDeltaCurr = Config(deltaCurr.map + (relation -> newDCInstance))

      val oldDNInstance = deltaNext(relation)
      val newDNInstance = ntp.foldLeft(oldDNInstance)(_ + _)
      val newDeltaNext = Config(deltaNext.map + (relation -> newDNInstance))

      State(trie, pos, newConfig, newDeltaCurr, newDeltaNext)
    }

    def nextEpoch: State[T] = if (!changed) this else State(trie, pos, config, deltaNext, Config())

  }

  def immediateConsequence[T <: Value[T]](state: State[T]): State[T] = {
    Timers("TrieSemiEvaluator.immediateConsequence(State)") {
      implicit val vs: Semiring[T] = state.vs
      immediateConsequence(state, state.trie, Vector(Assignment.Empty()), deltaDone = false)
    }
  }

  // Applies a RuleTrie to a configuration
  def immediateConsequence[T <: Value[T]](
                                           state: State[T],
                                           trie: RuleTrie,
                                           assignments: Vector[Assignment[T]],
                                           deltaDone: Boolean
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
      // Extend with full configuration only if there is the possibility to skip work later
      if (subTrie.numLiterals > 0 || deltaDone) {
        val ax3 = extendAssignments(literal, nextState.config, ax2)
        nextState = immediateConsequence(nextState, subTrie, ax3, deltaDone)
      }

      // Skip work only if never skipped work in the past
      if (!deltaDone) {
        val ax4 = extendAssignments(literal, nextState.deltaCurr, ax2)
        nextState = immediateConsequence(nextState, subTrie, ax4, deltaDone = true)
      }
    }

    // Step 2: Process leaves
    if (deltaDone) {
      for (rule <- trie.leaves) {
        implicit val vs: Semiring[T] = state.vs
        val newTuples = ax2.map(_ * Value(rule.lineage, state.pos)).map(_.toTuple(rule.head))
        nextState = nextState.addTuples(rule.head.relation, newTuples)
      }
    }

    nextState
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
