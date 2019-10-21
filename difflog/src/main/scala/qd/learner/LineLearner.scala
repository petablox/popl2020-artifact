package qd
package learner

import qd.Semiring.FValueSemiringObj
import qd.evaluator.Evaluator
import qd.problem.Problem
import qd.tokenvec.{Line, TokenVec}
import qd.util.Contract

object LineLearner extends Learner {

  override val toString: String = "LineLearner"

  override def learn(problem: Problem, evaluator: Evaluator, scorer: Scorer, tgtLoss: Double, maxIters: Int): State = {
    val trace = descend(problem, evaluator, scorer, tgtLoss, maxIters)
    val bestState = trace.minBy(_.loss)
    Learner.reinterpret(problem, evaluator, scorer, bestState)
  }

  def simplifyIfSolutionPoint(problem: Problem, state: State): Option[TokenVec] = {
    val usefulTokens = (for ((rel, refOut) <- problem.discreteIDB.toSeq;
                             tuple <- refOut;
                             token <- state.cOut(rel)(tuple).l.tokenSet)
                        yield token).toSet
    val eliminableTokens = problem.allTokens -- usefulTokens

    val isSolutionPoint = problem.outputRels.forall { relation =>
      val expectedTuples = problem.discreteIDB(relation)
      val unexpectedTuples = state.cOut(relation).support.filterNot { case (t, _) => expectedTuples.contains(t) }
      unexpectedTuples.forall { case (_, FValue(_, l)) => (l.tokenSet & eliminableTokens).nonEmpty }
    }

    if (isSolutionPoint) Some(TokenVec(problem.allTokens, token => if (usefulTokens.contains(token)) 1.0 else 0.0))
    else None
  }

  def descend(problem: Problem, evaluator: Evaluator, scorer: Scorer, tgtLoss: Double, maxIters: Int): Vector[State] = {
    val random = new scala.util.Random()

    var currPos = TokenVec(problem.allTokens.map(token => token -> (0.25 + random.nextDouble() / 2)).toMap)
    var currOut = evaluator(problem.rules, currPos, problem.edb)
    var grad = scorer.gradientLoss(currPos, currOut, problem.idb, problem.outputRels)
    var currLoss = scorer.loss(currOut, problem.idb, problem.outputRels)
    var currState = State(currPos, currOut, grad, currLoss)
    var ans = Vector(currState)

    var step = currPos

    val NUM_FWD_STEPS = 25
    val NUM_BWD_STEPS = 5
    val SQRT_NUM_DIMEN = Math.sqrt(problem.allTokens.size.toDouble)
    val LEARNING_RATE = 0.01

    implicit val vs: VecValueSemiring[FValue] = VecValueSemiring[FValue](NUM_FWD_STEPS + NUM_BWD_STEPS)
    val vecEDB = problem.edb.map(v => VecValue(Vector.fill(NUM_FWD_STEPS + NUM_BWD_STEPS)(v)))

    while (ans.size < maxIters && currLoss >= tgtLoss && grad.abs > 0 && step.abs > 0.0) {
      val delta0 = grad * LEARNING_RATE

      val tauFwd = Math.pow(SQRT_NUM_DIMEN / delta0.abs, 1.0 / NUM_FWD_STEPS)
      val tauBwd = Math.pow(SQRT_NUM_DIMEN / delta0.abs, 1.0 / NUM_BWD_STEPS)
      val fwdDeltas: IndexedSeq[TokenVec] = for (i <- Range(0, NUM_FWD_STEPS)) yield delta0 * Math.pow(tauFwd, i + 1.0)
      val bwdDeltas: IndexedSeq[TokenVec] = for (i <- Range(0, NUM_BWD_STEPS)) yield delta0 * Math.pow(tauBwd, i + 1.0) * -1
      val deltas = fwdDeltas ++ bwdDeltas
      Contract.assert(deltas.length == NUM_FWD_STEPS + NUM_BWD_STEPS)

      val line = deltas.map(delta => currPos - delta)
      val clippedLine = line.map(_.clip(0.0, 1.0).clip(0.01, 0.99, currPos))

      val cvf = evaluator[VecValue[FValue]](problem.rules, Line(clippedLine), vecEDB)
      val configs = Line.invert(cvf)
      Contract.assert(clippedLine.length == configs.length)
      val lineOut = for (((pos, out), stepIndex) <- clippedLine.zip(configs).zipWithIndex)
                    yield {
                      val loss = scorer.loss(out, problem.idb, problem.outputRels)
                      (stepIndex, pos, out, loss)
                    }

      val (stepIndex, nextPos, nextOut, nextLoss) = lineOut.minBy(_._4)
      val oldPos = currPos
      currPos = nextPos
      currOut = nextOut
      grad = scorer.gradientLoss(currPos, currOut, problem.idb, problem.outputRels)
      currLoss = nextLoss
      currState = State(currPos, currOut, grad, currLoss)

      ans = ans :+ currState
      step = currPos - oldPos

      // scribe.debug(s"  grad: $grad")
      scribe.info(s"  $currLoss, ${ans.map(_.loss).min}, ${currPos.abs}, ${grad.abs}, ${step.abs}, $stepIndex")
    }
    scribe.info(s"#Iterations: ${ans.size}.")

    ans
  }

}
