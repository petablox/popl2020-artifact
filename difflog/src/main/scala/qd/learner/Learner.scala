package qd
package learner

import qd.evaluator.Evaluator
import qd.instance.Config
import qd.problem.Problem
import qd.tokenvec.TokenVec
import qd.util.{Contract, Random, Timers}

case class State(pos: TokenVec, cOut: Config[FValue], grad: TokenVec, loss: Double)

object State {
  def apply(problem: Problem, evaluator: Evaluator, scorer: Scorer, pos: TokenVec): State = {
    State(problem, evaluator, scorer, pos, problem.edb)
  }

  def apply(problem: Problem, evaluator: Evaluator, scorer: Scorer, pos: TokenVec, oldCOut: Config[FValue]): State = {
    val cOut = Timers("State.apply: evaluator") {
      val repositionedIDB = Config.reposition(oldCOut, pos)
      evaluator(problem.rules, pos, repositionedIDB)
    }
    val grad = scorer.gradientLoss(pos, cOut, problem.idb, problem.outputRels)
    val loss = scorer.loss(cOut, problem.idb, problem.outputRels)
    State(pos, cOut, grad, loss)
  }
}

abstract class Learner {
  override def toString: String
  def learn(problem: Problem, evaluator: Evaluator, scorer: Scorer, tgtLoss: Double, maxIters: Int): State
}

object Learner {

  val STD_LEARNERS: Map[String, Learner] =
    Set(NewtonRootLearner, HybridAnnealingLearner).map(learner => learner.toString -> learner).toMap

  def sampleState(
                   problem: Problem,
                   evaluator: Evaluator,
                   scorer: Scorer,
                   oldCOut: Config[FValue]
                 ): State = {
    val initialPos = TokenVec(problem.allTokens.map(token => token -> Random.nextDouble(0.25, 0.75)).toMap)
    State(problem, evaluator, scorer, initialPos, oldCOut)
  }

  def sampleState(problem: Problem, evaluator: Evaluator, scorer: Scorer): State = {
    sampleState(problem, evaluator, scorer, problem.edb)
  }


  def trySeparate(problem: Problem, evaluator: Evaluator, scorer: Scorer, curState: State, acceptLoss : Double) : Option[State] = {

    val cOut = curState.cOut
    val cPos = curState.pos
    val cWeights = problem.allTokens.map( x => cPos(x).v)
    val ws = cWeights.toVector.sorted

    val step = Math.min(1, ws.size / 5)
    val idx = Range(1, ws.size).map(x => x * step).filter( x => x < ws.size) :+ 1

    for (theta <- idx.map( i => ws(i))) {
      val newPos = TokenVec(problem.allTokens, token => if ( cPos(token).v >= theta) 1.0 else 0.0)
      val newState = State(problem, evaluator, scorer, newPos, cOut)
      if (newState.loss <= acceptLoss) {
        scribe.info("after separation, the loss is within acceptable range")
        return Some(newState)
      }
    }

    None
  }

  def simplifyIfSolutionPoint(problem: Problem, evaluator: Evaluator, scorer: Scorer, cOut: Config[FValue]): Option[State] = {
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
      val newState = State(problem, evaluator, scorer, newPos, cOut)
      if (newState.loss <= 1.01) {
        scribe.info("... and also a solution point.")
        Some(newState)
      } else {
        scribe.info(s"... but not a solution point (newLoss = ${newState.loss}). Not terminating!")
        None
      }
    } else None
  }

  def findForbiddenTokens(problem: Problem, cOut: Config[FValue]): Set[Token] = {
    val ans = for (rel <- problem.outputRels;
                   (t, v) <- cOut(rel).support if !problem.discreteIDB(rel).contains(t);
                   tokenSet = v.l.tokenSet if tokenSet.size == 1)
              yield tokenSet.head
    if (Contract.VERBOSE) {
      scribe.info(s"  Found forbidden tokens: ${ans.mkString(", ")}")
    }
    ans
  }

  def reinterpret(problem: Problem, evaluator: Evaluator, scorer: Scorer, state: State): State = {
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
    State(problem, evaluator, scorer, newPos, state.cOut)
  }

}