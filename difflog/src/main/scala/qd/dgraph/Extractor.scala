package qd
package dgraph

import qd.dgraph.Derivation.DGraph
import qd.util.{Contract, Timers}

abstract class Extractor {
  override def toString: String
  def apply(rules: Set[Rule], edb: DGraph): DGraph
}

object Extractor {
  val STD_EXTRACTORS: Map[String, Extractor] =
    Set(NaiveExtractor).map(evaluator => evaluator.toString -> evaluator)
                       .toMap
}

object NaiveExtractor extends Extractor {

  override val toString: String = "NaiveExtractor"

  override def apply(rules: Set[Rule], edb: DGraph): DGraph = {
    var state = State(rules, edb, changed = true)
    while (state.changed) { state = immediateConsequence(state.nextEpoch) }
    state.graph
  }

  case class State(rules: Set[Rule], graph: DGraph, changed: Boolean) {

    def addTuples(relation: Relation, newClauses: Seq[Clause]): State = {
      val oldInstance = graph.getOrElse(relation, Map())
      var newInstance = oldInstance
      var newChanged = changed
      for (clause <- newClauses) {
        val oldDerivations = newInstance.getOrElse(clause.conclusion, Set())
        if (!oldDerivations.contains(clause)) {
          val newDerivations = oldDerivations + clause
          newInstance = newInstance + (clause.conclusion -> newDerivations)
          newChanged = true
        }
      }
      val newConfig = graph + (relation -> newInstance)
      State(rules, newConfig, newChanged)
    }

    def nextEpoch: State = if (!changed) this else State(rules, graph, changed = false)

  }

  def immediateConsequence(state: State): State = {
    Timers("NaiveExtractor.immediateConsequence(State)") {
      state.rules.foldLeft(state)((nextState, rule) => ruleConsequence(nextState, rule))
    }
  }

  def ruleConsequence(state: State, rule: Rule): State = {
    var assignments = Vector(FatAssignment.Empty)
    for (literal <- rule.body) {
      assignments = extendAssignments(literal, state.graph, assignments)
    }

    val newClauses = assignments.map(assgn => Clause(assgn.toTuple(rule.head), rule, assgn.antecedents))
    state.addTuples(rule.head.relation, newClauses)
  }

  def isConsistent(t: DTuple, f: IndexedSeq[Option[Constant]]): Boolean = {
    Contract.require(t.length == f.length)
    f.indices.filter(i => f(i).nonEmpty).forall(i => f(i).get == t(i))
  }

  def extendAssignments(literal: Literal, graph: DGraph, assignments: Vector[FatAssignment]): Vector[FatAssignment] = {
    for (assignment <- assignments;
         f = assignment.toFilter(literal);
         instance = graph.getOrElse(literal.relation, Map());
         (tuple, _) <- instance.filterKeys(tuple => isConsistent(tuple, f));
         newAssignment <- extendAssignment(literal, tuple, assignment))
      yield newAssignment
  }

  def extendAssignment(literal: Literal, tuple: DTuple, assignment: FatAssignment): Option[FatAssignment] = {
    var ans = assignment
    for ((par, field) <- literal.fields.zip(tuple)) {
      par match {
        case v @ Variable(_, _) =>
          if (!ans.contains(v)) ans = ans + (v -> field)
          else if (ans(v) != field) return None
        case Constant(c, _) => if (c != field) return None
      }
    }
    Some(ans.addAntecedent(tuple))
  }

}
