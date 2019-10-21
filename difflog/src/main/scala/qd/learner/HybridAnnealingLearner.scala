package qd
package learner

import qd.evaluator.Evaluator
import qd.problem.Problem
import qd.tokenvec.TokenVec
import qd.util.{Contract, Random, Timers}

object HybridAnnealingLearner extends Learner {

  override val toString: String = "HybridAnnealingLearner"

  override def learn(problem: Problem, evaluator: Evaluator, scorer: Scorer, tgtLoss: Double, maxIters: Int): State = {
    Timers("HybridAnnealingLearner.learn") {
      // 1. Start with a random initial state
      var forbiddenTokens: Set[Token] = Set()
      var currState = Learner.sampleState(problem, evaluator, scorer)
      var bestState = currState
      var stepSize = 1.0

      // 2. Repeatedly choose next state until solution is found
      //    a. Once every MCMC_FREQ iterations, choose this next state by MCMC+SimulatedAnnealing criterion
      //    b. Otherwise, choose next state by performing a conventional gradient descent step
      val MCMC_FREQ = 30
      var numIters = 0
      if (Contract.VERBOSE) {
        scribe.info(problem.rules.toVector.sortBy(_.lineage.toString)
                           .map(rule => s"  $rule")
                           .mkString(System.lineSeparator(), System.lineSeparator(), ""))
      }
      while (numIters < maxIters && currState.loss >= tgtLoss) {
        val newlyForbiddenTokens = Learner.findForbiddenTokens(problem, currState.cOut)
        if (newlyForbiddenTokens.nonEmpty) {
          forbiddenTokens = forbiddenTokens ++ newlyForbiddenTokens
        }

        if (numIters % MCMC_FREQ == 0) {
          currState = nextStateMCMC(problem, evaluator, scorer, currState, forbiddenTokens, numIters / MCMC_FREQ)
          stepSize = 1.0
        } else {
          val oldState = currState
          currState = NewtonRootLearner.nextState(problem, evaluator, scorer, currState, forbiddenTokens)
          stepSize = (currState.pos - oldState.pos).abs
        }

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
          /* for ((token, value) <- currState.pos.toVector.sortBy(_._1.toString)) {
            scribe.info(s"  $token: $value")
          } */

          /* for (rel <- problem.outputRels; (t, v) <- currState.cOut(rel).support) {
            if (problem.discreteIDB(rel).contains(t)) {
              scribe.info(s"$t: ${v.l} (Desired)")
            } else {
              scribe.info(s"$t: ${v.l} (Undesired)")
            }
          } */
        }
      }
      scribe.info(s"#Iterations: $numIters.")

      Learner.reinterpret(problem, evaluator, scorer, bestState)
    }
  }

  def nextStateMCMC(
                     problem: Problem,
                     evaluator: Evaluator,
                     scorer: Scorer,
                     currState: State,
                     forbiddenTokens: Set[Token],
                     iteration: Int
                   ): State = {
    require(iteration >= 0)
    val solutionPointOpt = Learner.simplifyIfSolutionPoint(problem, evaluator, scorer, currState.cOut)
//    val solutionPointOpt = Learner.trySeparate(problem, evaluator, scorer, currState, 0.1)
    solutionPointOpt.getOrElse {
      /* val newPos = TokenVec(problem.allTokens,
                            token => if (!forbiddenTokens.contains(token)) Random.nextDouble() else 0.0) */
      val newPos = TokenVec(problem.allTokens,
                            token => {
                              if (!forbiddenTokens.contains(token)) {
                                val coin = Random.nextDouble()
                                val prev = currState.pos(token).v
                                if (coin < 0.5) prev * Math.sqrt(2 * coin) else (1 - (1 - prev) * Math.sqrt(2 * (1 - coin)))
                              } else 0
                            })
      val proposedState = State(problem, evaluator, scorer, newPos, currState.cOut)

      val c = 1.0e-3
      val k0 = 5.0
      val temperature = 1.0 / (c * Math.log(k0 + iteration))
      def pi(negativeLoss: Double): Double = Math.exp(negativeLoss / temperature)

      val piCurr = pi(-currState.loss)
      val piProposed = pi(-proposedState.loss)
      val probAccept = Math.min(1.0, piProposed / piCurr)
      val coin = Random.nextDouble()

      scribe.info(s"  c: $c, k0: $k0, iteration: $iteration, temperature: $temperature")
      scribe.info(s"  currState.loss: ${currState.loss}, piCurr: $piCurr")
      scribe.info(s"  proposedState.loss: ${proposedState.loss}, piProposed: $piProposed")
      scribe.info(s"  probAccept: $probAccept, coin: $coin")

      if (coin < probAccept) {
        scribe.info("  Accepted MCMC sample")
        proposedState
      } else {
        scribe.info("  Rejected MCMC sample")
        currState
      }
    }
  }

}
