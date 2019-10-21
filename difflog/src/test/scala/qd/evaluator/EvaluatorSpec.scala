package qd
package evaluator

import org.scalatest.FunSuite
import data.graphs.{Graphs, Reachability}
import qd.Semiring.FValueSemiringObj

class EvaluatorSpec(evaluator: Evaluator) extends FunSuite {
  for ((programName, rules) <- Reachability.Programs; graph <- Graphs.Graphs) {
    test(s"Applying evaluator $evaluator to program $programName and graph ${graph.name}") {
      val idb = evaluator(rules, _ => FValueSemiringObj.One, graph.edb)
      val produced = idb(Graphs.path)
      assert(produced.support.forall(_._1.length == 2))
      assert(produced.support.map(tv => (tv._1(0), tv._1(1))).toSet == graph.reachable)
      assert(produced.support.forall(_._2.v >= 1.0))
    }
  }
}

class NaiveEvaluatorSpec extends EvaluatorSpec(NaiveEvaluator)
class SeminaiveEvaluatorSpec extends EvaluatorSpec(SeminaiveEvaluator)
class TrieEvaluatorSpec extends EvaluatorSpec(TrieEvaluator)
class TrieSemiEvaluatorSpec extends EvaluatorSpec(TrieSemiEvaluator)
class TrieJoinEvaluatorSpec extends EvaluatorSpec(TrieJoinEvaluator)
