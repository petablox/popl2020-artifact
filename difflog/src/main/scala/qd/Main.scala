package qd

import qd.Semiring.FValueSemiringObj
import qd.dgraph.Extractor
import qd.evaluator.Evaluator
import qd.learner.{Learner, Scorer}
import qd.problem.{ALPSParser, Problem, QDParser, SouffleWriter}
import qd.stochasticlearner.{StochasticLearner, StochasticScorer}
import qd.util.Timers.Timer
import qd.util.{Contract, Counters, Timers}

import scala.io.Source

object Main extends App {

  def readQDProblem(filename: String): Problem = {
    val inputString = Source.fromFile(filename).mkString
    new QDParser().parse(inputString)
  }

  def readALPSProblem(dataFilename: String, templateFilename: String): Problem = {
    val dataStr = Source.fromFile(dataFilename).mkString
    val templateStr = Source.fromFile(templateFilename).mkString
    val ans = ALPSParser.parse(dataStr, templateStr)
    if (Contract.VERBOSE) {
      for (rule <- ans.rules.toVector.sortBy(_.lineage.toString)) {
        scribe.info(rule.toString)
      }
    }
    ans
  }

  Timers("Main") {

    scribe.info(s"Hello! Difflog invoked with arguments ${args.mkString("[", ", ", "]")}")

    args match {
      case Array("eval", queryFilename, evaluatorName) =>
        val query = readQDProblem(queryFilename)
        val evaluator = Evaluator.STD_EVALUATORS(evaluatorName)

        val idb = evaluator(query.rules, query.pos, query.edb)
        for (rel <- query.outputRels) {
          for ((t, v) <- idb(rel).support.sortBy(-_._2.v)) {
            println(s"$v: ${rel.name}$t")
            scribe.trace(s"$v: ${rel.name}$t")
          }
        }
        for (rel <- query.inventedRels) {
          for ((t, v) <- idb(rel).support.sortBy(-_._2.v)) {
            scribe.trace(s"$v: ${rel.name}$t")
          }
        }

      case Array("learn", queryFilenameTrain, learnerName, evaluatorName, scorerName, tgtLossStr, maxItersStr) =>
        val queryTrain = readQDProblem(queryFilenameTrain)
        val learner = Learner.STD_LEARNERS(learnerName)
        val evaluator = Evaluator.STD_EVALUATORS(evaluatorName)
        val scorer = Scorer.STD_SCORERS(scorerName)
        val tgtLoss = tgtLossStr.toDouble
        val maxIters = maxItersStr.toInt
        Contract.require(maxIters > 0)

        learner.learn(queryTrain, evaluator, scorer, tgtLoss, maxIters)
        ???

      case Array("tab2", _*) => ???
      case Array("alps", dataFilename, templateFilename,
                         learnerName, evaluatorName, scorerName,
                         tgtLossStr, maxItersStr) =>
        val query = readALPSProblem(dataFilename, templateFilename)
        val learner = Learner.STD_LEARNERS(learnerName)
        val evaluator = Evaluator.STD_EVALUATORS(evaluatorName)
        val scorer = Scorer.STD_SCORERS(scorerName)
        val tgtLoss = tgtLossStr.toDouble
        val maxIters = maxItersStr.toInt
        Contract.require(maxIters > 0)

        val result = learner.learn(query, evaluator, scorer, tgtLoss, maxIters)
        println(s"// Achieved loss ${result.loss}")
        val weightedRules = query.rules.map(rule => (Value(rule.lineage, result.pos), rule))
        weightedRules.filter({ case (weight, _) => FValueSemiringObj.nonZero(weight) })
                     .toVector
                     .sortBy(-_._1.v)
                     .map({ case (weight, rule) => s"$weight: $rule" })
                     .foreach(println)

      case Array("alps-noise", dataFilename, templateFilename,
                               learnerName, evaluatorName, scorerName,
                               tgtLossStr, maxItersStr) =>
        val query = readALPSProblem(dataFilename, templateFilename).injectNoise()
        val learner = Learner.STD_LEARNERS(learnerName)
        val evaluator = Evaluator.STD_EVALUATORS(evaluatorName)
        val scorer = Scorer.STD_SCORERS(scorerName)
        val tgtLoss = tgtLossStr.toDouble
        val maxIters = maxItersStr.toInt
        Contract.require(maxIters > 0)

        val result = learner.learn(query, evaluator, scorer, tgtLoss, maxIters)
        println(s"// Achieved loss ${result.loss}")
        val weightedRules = query.rules.map(rule => (Value(rule.lineage, result.pos), rule))
        weightedRules.filter({ case (weight, _) => FValueSemiringObj.nonZero(weight) })
          .toVector
          .sortBy(-_._1.v)
          .map({ case (weight, rule) => s"$weight: $rule" })
          .foreach(println)

      case Array("alps-2", dataFilename, templateFilename,
                           learnerName, extractorName, evaluatorName, scorerName,
                           nsamplesStr, tgtLossStr, maxItersStr) =>
        val query = readALPSProblem(dataFilename, templateFilename)
        val learner = StochasticLearner.STD_STOCHASTIC_LEARNERS(learnerName)
        val extractor = Extractor.STD_EXTRACTORS(extractorName)
        val evaluator = Evaluator.STD_EVALUATORS(evaluatorName)
        val scorer = StochasticScorer.STD_SCORERS(scorerName)
        val nsamples = nsamplesStr.toInt
        val tgtLoss = tgtLossStr.toDouble
        val maxIters = maxItersStr.toInt
        Contract.require(maxIters > 0)

        val result = learner.learn(query, extractor, evaluator, scorer, nsamples, tgtLoss, maxIters)
        println(s"// Achieved loss ${result.loss}")
        val weightedRules = query.rules.map(rule => (Value(rule.lineage, result.pos), rule))
        weightedRules.filter({ case (weight, _) => FValueSemiringObj.nonZero(weight) })
                     .toVector
                     .sortBy(-_._1.v)
                     .map({ case (weight, rule) => s"$weight: $rule" })
                     .foreach(println)

      case Array("2souffle", dataFilename, templateFilename, outputDirectoryName) =>
        val query = readALPSProblem(dataFilename, templateFilename)
        SouffleWriter.write(query, outputDirectoryName)

      case Array("ntp-learn", _*) => ???
      case Array("ntp-query", _*)=> ???
      case _ =>
        val stdLearnersStr = Learner.STD_LEARNERS.keys.mkString(" | ")
        val stdStochasticLearnersStr = StochasticLearner.STD_STOCHASTIC_LEARNERS.mkString(" | ")
        val stdEvaluatorsStr = Evaluator.STD_EVALUATORS.keys.mkString(" | ")
        val stdExtractorsStr = Extractor.STD_EXTRACTORS.keys.mkString(" | ")
        val stdScorersStr = Scorer.STD_SCORERS.keys.mkString(" | ")
        println(
          s"""Usage:
             |
             |  1. eval query.qd
             |          [ $stdEvaluatorsStr ]
             |     Evaluates the query query.qd using the specified evaluator
             |
             |  2. learn problem.qd
             |           [ $stdLearnersStr ]
             |           [ $stdEvaluatorsStr ]
             |           [ $stdScorersStr ]
             |           tgtLoss
             |           maxIters
             |     Solves the query synthesis problem described in problem.qd
             |
             |  3. tab2 problem.qd
             |          test.qd
             |          [ $stdEvaluatorsStr ]
             |          [ $stdScorersStr ]
             |          tgtLoss
             |          maxIters
             |     Produces the statistics needed for Table 2 of the Difflog paper
             |
             |  4. alps data.d
             |          templates.tp
             |          [ $stdLearnersStr ]
             |          [ $stdEvaluatorsStr ]
             |          [ $stdScorersStr ]
             |          tgtLoss
             |          maxIters
             |     Runs Difflog in the ALPS setting
             |
             |  5. alps-2 data.d
             |            templates.tp
             |            [ $stdStochasticLearnersStr ]
             |            [ $stdExtractorsStr ]
             |            [ $stdEvaluatorsStr ]
             |            [ $stdScorersStr ]
             |            nsamples
             |            tgtLoss
             |            maxIters
             |     Runs Difflog with probabilistic sampling of derivation graphs
             |
             | 6. 2souffle data.d
             |             templates.tp
             |             outputDirectory
             |    Translates the ALPS benchmarks into a format suitable for consumption by Souffle and Prosynth
           """.stripMargin)
    }

  }

  scribe.info {
    val strs = for ((name, Timer(duration, invocations)) <- Timers.getSnapshot.toVector.sortBy(-_._2.duration))
               yield s"$name: ${duration / 1.0e9} seconds, $invocations invocations."
    if (strs.nonEmpty) "Timers:" + System.lineSeparator() + strs.mkString(System.lineSeparator())
    else "No timers enabled"
  }
  scribe.info {
    val strs = for ((name, count) <- Counters.getSnapshot.toVector.sortBy(-_._2)) yield s"$name: $count"
    if (strs.nonEmpty) "Counters:" + System.lineSeparator() + strs.mkString(System.lineSeparator())
    else "No counters enabled"
  }
  scribe.info("Bye!")

}
