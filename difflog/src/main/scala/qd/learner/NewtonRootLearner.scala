package qd
package learner

import qd.evaluator.Evaluator
import qd.problem.Problem
import qd.tokenvec.TokenVec
import qd.util.{Contract, Timers}

object NewtonRootLearner extends Learner {

  override val toString: String = "NewtonRootLearner"

  override def learn(problem: Problem, evaluator: Evaluator, scorer: Scorer, tgtLoss: Double, maxIters: Int): State = {
    Timers("NewtonRootLearner.learn") {
      var currState = Learner.sampleState(problem, evaluator, scorer)
      var bestState = currState
      var stepSize = 1.0

      var numIters = 0
      while (numIters < maxIters && currState.loss >= tgtLoss && currState.grad.abs > 0 && stepSize > 0.0) {
        val oldState = currState
        currState = nextState(problem, evaluator, scorer, currState, Set())
        stepSize = (currState.pos - oldState.pos).abs

        if (currState.loss < bestState.loss) {
          bestState = currState
        }
        numIters = numIters + 1

        // scribe.debug(s"  currState.grad: ${currState.grad}")
        scribe.info(s"  ${currState.loss}, ${bestState.loss}, ${currState.pos.abs}, " +
                    s"${currState.grad.abs}, $stepSize")
        if (Contract.VERBOSE) {
          val posStr = currState.pos.toVector.sortBy(_._1.toString).map({ case (_, v) => s"$v" }).mkString(", ")
          scribe.info(s"  ${currState.loss}, $posStr")
        }
      }
      scribe.info(s"#Iterations: $numIters.")

      Learner.reinterpret(problem, evaluator, scorer, bestState)
    }
  }

  def nextState(problem: Problem, evaluator: Evaluator, scorer: Scorer, currState: State, forbiddenTokens: Set[Token]): State = {
    val solutionPointOpt = Learner.simplifyIfSolutionPoint(problem, evaluator, scorer, currState.cOut)
    solutionPointOpt.getOrElse {
      val State(currPos, _, currGrad, currLoss) = currState

      /* // Repeatedly lower delta until the step is actually heading downwards
      var delta = currGrad.unit * currLoss / currGrad.abs
      var nextPos = (currPos - delta).clip(0.0, 1.0).clip(0.01, 0.99, currPos)
      var nextState = State(problem, evaluator, scorer, nextPos)

      while (nextState.loss > currState.loss) {
        scribe.info(s"  Halving delta! ${delta.abs}")
        delta = delta * 0.5
        nextPos = (currPos - delta).clip(0.0, 1.0).clip(0.01, 0.99, currPos)
        nextState = State(problem, evaluator, scorer, nextPos)
      }

      nextState */

      val delta = currGrad.unit * currLoss / currGrad.abs
      val nextPos = (currPos - delta).clip(0.0, 1.0).clip(0.01, 0.99, currPos)
      val newPos = TokenVec(problem.pos.keySet, token => {
        if (forbiddenTokens.contains(token)) 0.0
        else nextPos(token).v
      })
      State(problem, evaluator, scorer, newPos, currState.cOut)
    }
  }

}
