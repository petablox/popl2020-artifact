package qd.stochasticlearner

import qd.Semiring.FValueSemiringObj
import qd.dgraph.Derivation.DGraph
import qd.instance.Config
import qd.learner.{L2Scorer, Scorer}
import qd.stochasticlearner.StochasticLearner.StochasticConfigs
import qd.tokenvec.TokenVec
import qd.{DTuple, FValue, Relation}

abstract class StochasticScorer {

  override def toString: String
  val baseScorer: Scorer

  def gradient(pos: TokenVec, cOut: StochasticConfigs, relation: Relation, tuple: DTuple): TokenVec = {
    val pathSamples = cOut.map(_(relation)(tuple))

    val gradients = pathSamples.map { case (pathValue, _) =>
      val vt = pathValue.v
      val prov = pathValue.l.toVector
      val freq = prov.groupBy(identity).map { case (token, value) => token -> value.size }
      val ans = pos.keySet.map { token =>
        val dvtDtoken = freq.getOrElse(token, 0) * vt / pos(token).v
        token -> (if (!dvtDtoken.isNaN) dvtDtoken else 0.0)
      }
      TokenVec(ans.toMap)
    }
    val totalGradient = gradients.foldLeft(TokenVec(pos.keySet, _ => 0))(_ + _)
    val ans = totalGradient * 1.0 / pathSamples.size.toDouble
    ans
  }

  def loss(sconfig: StochasticConfigs, cRef: Config[FValue], rel: Relation, t: DTuple): Double

  def loss(dgraph: DGraph, outputRels: Set[Relation], sconfig: StochasticConfigs, cRef: Config[FValue]): Double = {
    val twiseLoss = for (relation <- outputRels.toVector; tuple <- dgraph(relation).keys)
                    yield loss(sconfig, cRef, relation, tuple)
    twiseLoss.sum
  }

  def gradientLoss(pos: TokenVec, sconfig: StochasticConfigs, cRef: Config[FValue], rel: Relation, t: DTuple): TokenVec

  def gradientLoss(
                    dgraph: DGraph,
                    outputRels: Set[Relation],
                    pos: TokenVec,
                    sconfig: StochasticConfigs,
                    cRef: Config[FValue]
                  ): TokenVec = {
    val twiseGradientLoss = for (relation <- outputRels.toVector; tuple <- dgraph(relation).keys)
                            yield gradientLoss(pos, sconfig, cRef, relation, tuple)
    val zero = TokenVec(pos.keySet, _ => 0)
    twiseGradientLoss.foldLeft(zero)(_ + _)
  }

}

object StochasticScorer {
  val STD_SCORERS: Map[String, StochasticScorer] =
    Set(StochasticL2Scorer).map(scorer => scorer.toString -> scorer).toMap
}

object StochasticL2Scorer extends StochasticScorer {

  override def toString: String = "StochasticL2Scorer"

  override val baseScorer: Scorer = L2Scorer

  def loss(sconfig: StochasticConfigs, cRef: Config[FValue], rel: Relation, t: DTuple): Double = {
    val samples = sconfig.map(_(rel)(t))
    val vOut = samples.map(_._1).foldLeft(FValueSemiringObj.Zero)(_ + _).v / samples.size
    val vRef = cRef(rel)(t).v
    (vOut - vRef) * (vOut - vRef)
  }

  override def gradientLoss(
                             pos: TokenVec,
                             sconfig: StochasticConfigs,
                             cRef: Config[FValue],
                             rel: Relation,
                             tuple: DTuple
                           ): TokenVec = {
    val pathSamples = sconfig.map(_(rel)(tuple))
    val pathValues = pathSamples.map(_._1.v)
    val avgPathValue = pathValues.sum / pathValues.size
    gradient(pos, sconfig, rel, tuple) * (avgPathValue - cRef(rel)(tuple).v) * 2
  }

}
