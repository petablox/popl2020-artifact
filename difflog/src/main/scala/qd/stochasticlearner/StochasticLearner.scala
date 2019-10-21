package qd
package stochasticlearner

import qd.Semiring.FValueSemiringObj
import qd.dgraph.Derivation.{DGraph, samplePath}
import qd.dgraph.{Clause, Extractor}
import qd.evaluator.Evaluator
import qd.instance.Config
import qd.problem.Problem
import qd.tokenvec.TokenVec
import qd.util.{Random, Timers}

case class StochasticState(pos: TokenVec, cOut: Config[FValue], loss: Double)

object StochasticState {
  def apply(problem: Problem, evaluator: Evaluator, scorer: StochasticScorer, pos: TokenVec): StochasticState = {
    StochasticState(problem, evaluator, scorer, pos, problem.edb)
  }

  def apply(
             problem: Problem,
             evaluator: Evaluator,
             scorer: StochasticScorer,
             pos: TokenVec,
             oldCOut: Config[FValue]
           ): StochasticState = {
    val cOut = Timers("StochasticState.apply: evaluator") {
      val repositionedIDB = Config.reposition(oldCOut, pos)
      evaluator(problem.rules, pos, repositionedIDB)
    }
    val loss = scorer.baseScorer.loss(cOut, problem.idb, problem.outputRels)
    StochasticState(pos, cOut, loss)
  }
}

abstract class StochasticLearner {
  override def toString: String
  def learn(
             problem: Problem,
             extractor: Extractor,
             evaluator: Evaluator,
             scorer: StochasticScorer,
             nsamples: Int,
             tgtLoss: Double,
             maxIters: Int
           ): StochasticState
}

object StochasticLearner {
  val STD_STOCHASTIC_LEARNERS: Map[String, StochasticLearner] =
    Set(StochasticNRLearner).map(learner => learner.toString -> learner).toMap

  def sampleState(
                   problem: Problem,
                   evaluator: Evaluator,
                   scorer: StochasticScorer,
                   oldCOut: Config[FValue]
                 ): StochasticState = {
    val initialPos = TokenVec(problem.allTokens.map(token => token -> Random.nextDouble(0.25, 0.75)).toMap)
    StochasticState(problem, evaluator, scorer, initialPos, oldCOut)
  }

  def sampleState(problem: Problem, evaluator: Evaluator, scorer: StochasticScorer): StochasticState = {
    sampleState(problem, evaluator, scorer, problem.edb)
  }

  type StochasticConfig = Map[Relation, Map[DTuple, (FValue, Vector[Clause])]]
  type StochasticConfigs = Vector[StochasticConfig]

  def samplePaths(graph: DGraph, outputRels: Set[Relation], pos: TokenVec, nsamples: Int): StochasticConfigs = {
    // TODO: Consider reusing paths
    Range(0, nsamples).map({ _ =>
      var ans: StochasticConfig = Map()
      for (relation <- outputRels; tuple <- graph(relation).keys) {
        ans = samplePath(graph, pos, relation, tuple, ans)
      }
      ans
    }).toVector
  }

  def simplifyIfSolutionPoint(
                               problem: Problem,
                               evaluator: Evaluator,
                               scorer: StochasticScorer,
                               cOut: Config[FValue]
                             ): Option[StochasticState] = {
    val usefulTokens = (for ((rel, refOut) <- problem.discreteIDB.toSeq;
                             tuple <- refOut;
                             token <- cOut(rel)(tuple).l.tokenSet)
      yield token).toSet
    val eliminableTokens = problem.allTokens -- usefulTokens

    val isSeparable = problem.outputRels.forall { relation =>
      val expectedTuples = problem.discreteIDB(relation)
      val unexpectedTuples = cOut(relation).support.filterNot { case (t, _) => expectedTuples.contains(t) }
      unexpectedTuples.forall { case (_, FValue(_, l)) => (l.tokenSet & eliminableTokens).nonEmpty }
    }

    if (isSeparable) {
      scribe.info("Current position is separable...")
      val newPos = TokenVec(problem.allTokens, token => if (usefulTokens.contains(token)) 1.0 else 0.0)
      val newState = StochasticState(problem, evaluator, scorer, newPos, cOut)
      if (newState.loss <= 0.0) {
        scribe.info("... and also a solution point.")
        Some(newState)
      } else {
        scribe.info(s"... but not a solution point (newLoss = ${newState.loss}). Not terminating!")
        None
      }
    } else None
  }

  def reinterpret(
                   problem: Problem,
                   evaluator: Evaluator,
                   scorer: StochasticScorer,
                   state: StochasticState
                 ): StochasticState = {
    val usefulTokens = (for ((rel, refOut) <- problem.discreteIDB.toSeq;
                             tuple <- refOut;
                             token <- state.cOut(rel)(tuple).l.tokenSet)
                        yield token).toSet
    val grayTokens = (for ((rel, refOut) <- state.cOut.map if problem.outputRels.contains(rel);
                           (tuple, value) <- refOut.support if !problem.discreteIDB(rel).contains(tuple);
                           token <- value.l.tokenSet)
                      yield token).toSet
    val exclusivelyUsefulTokens = usefulTokens -- grayTokens

    val newPos = TokenVec(problem.allTokens, token => if (exclusivelyUsefulTokens.contains(token)) 1.0
                                                      else if (grayTokens.contains(token)) state.pos(token).v
                                                      else 0.0)
    StochasticState(problem, evaluator, scorer, newPos, state.cOut)
  }
}
