package qd
package dgraph

import qd.Semiring.FValueSemiringObj
import qd.stochasticlearner.StochasticLearner.StochasticConfig
import qd.tokenvec.TokenVec
import qd.util.{Contract, Random, Timers}

sealed abstract class Derivation {
  def conclusion: DTuple
}
case class EDB(conclusion: DTuple) extends Derivation
case class Clause(conclusion: DTuple, rule: Rule, antecedents: IndexedSeq[DTuple]) extends Derivation {
  Contract.require(conclusion.signature == rule.head.relation.signature)
  Contract.require(rule.body.length == antecedents.length)
  Contract.require(rule.body.indices.forall { i =>
    rule.body(i).relation.signature == antecedents(i).signature
  })
}

object Derivation {

  type DGraph = Map[Relation, Map[DTuple, Set[Derivation]]]
  def apply(conclusion: DTuple): Derivation = EDB(conclusion)

  def samplePath(
                  graph: DGraph,
                  pos: TokenVec,
                  relation: Relation,
                  tuple: DTuple,
                  memo: StochasticConfig
                ): StochasticConfig = Timers("Derivation.samplePath") {
    samplePath(graph, pos, relation, tuple, memo, Set()).get
  }

  def samplePath(
                  graph: DGraph,
                  pos: TokenVec,
                  relation: Relation,
                  tuple: DTuple,
                  memo: StochasticConfig,
                  stack: Set[(Relation, DTuple)]
                ): Option[StochasticConfig] = {
    if (stack.contains((relation, tuple))) {
      None
    } else if (memo.contains(relation) && memo(relation).contains(tuple)) {
      Some(memo)
    } else {
      val derivations = graph(relation)(tuple)
      if (derivations.size == 1 && derivations.head.isInstanceOf[EDB]) {
        // the current tuple is an EDB, then job is done
        val ans = (FValueSemiringObj.One, Vector())
        val memoRel = memo.getOrElse(relation, Map())
        Some(memo + (relation -> (memoRel + (tuple -> ans))))
      } else {
        var remainingDerivations = derivations.map(_.asInstanceOf[Clause])
        val sj = stack + ((relation, tuple))
        // repeat sampling until a success
        while (remainingDerivations.nonEmpty) {
          // 1. Randomly sample a derivation
          /* val chosenClause = {
            val clauses = remainingDerivations
            val weightedClauses = clauses.map(clause => (clause, Value(clause.rule.lineage, pos).v))
            val hi = weightedClauses.map(_._2).sum
            var coin = Random.nextDouble(lo = 0, hi)
            var remainingClauses = weightedClauses.toVector
            while (coin > remainingClauses.head._2) {
              coin = coin - remainingClauses.head._2
              remainingClauses = remainingClauses.tail
            }
            remainingClauses.head._1
          } */
          val chosenClause = remainingDerivations.toVector(Random.nextInt(0, remainingDerivations.size))

          // 2. Randomly sample one hypothesis from the chosen derivation
          var remainingHypotheses = chosenClause.rule.body.map(_.relation).zip(chosenClause.antecedents).filterNot(stack)
          while (remainingHypotheses.nonEmpty) {
            val chosenHypothesisIndex = Random.nextInt(lo = 0, remainingHypotheses.size)
            val chosenHypothesis = remainingHypotheses(chosenHypothesisIndex)
            val relPrime = chosenHypothesis._1
            val tuplePrime = chosenHypothesis._2
            samplePath(graph, pos, relPrime, tuplePrime, memo, sj) match {
              case Some(memoPrime) =>
                val vPathPrime = memoPrime(relPrime)(tuplePrime)
                val ansValue = vPathPrime._1 * Value(chosenClause.rule.lineage, pos)
                val ansPath = vPathPrime._2 :+ chosenClause
                val ans = (ansValue, ansPath)
                val memoRel = memoPrime.getOrElse(relation, Map())
                return Some(memoPrime + (relation -> (memoRel + (tuple -> ans))))
              case None =>
                remainingHypotheses = remainingHypotheses.filterNot(_ == chosenHypothesis)
            }
          }

          remainingDerivations = remainingDerivations - chosenClause
        }
        None
      }
    }
  }

}