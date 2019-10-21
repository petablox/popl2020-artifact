# README #

### What is this repository for? ###

This repository contains the implementation of the Difflog differentiable Datalog system. This includes an evaluator for
Difflog programs and a system to learn classical Datalog programs from input-output data.

This forms the code and benchmark data for our IJCAI 2019 paper titled "Synthesizing Datalog Programs Using Numerical
Relaxation."

### How to compile, build, and run Difflog? ###

1. Install sbt. We recommend a version >= 1.1.1.

2. Run the command `sbt compile`.

3. To use Difflog to synthesize Datalog programs, invoke `sbt` and issue the following commands at the ensuing prompt:

   ```[info] Loading settings from plugins.sbt ...
   [info] ...
   ...
   sbt> run alps src/test/resources/ALPS/data/path.d src/test/resources/ALPS/templates/path.tp HybridAnnealingLearner NaiveEvaluator L2Scorer 0.01 1000
   ```

   The system will momentarily print logging information and the final synthesized program and associated metrics.

3. In general, the synthesis command is of the form:

   ```run alps data.d templates.tp learnerName evaluatorName scorerName targetLoss numIters```

   For the learner, evaluator, scorer, target loss and number of iterations, we recommend the values
   `HybridAnnealingLearner`, `NaiveEvaluator`, `L2Scorer`, `0.01` and `1000` respectively.

   Several data.d and templates.tp files can be found in the `src/test/resources/ALPS` directory. The user is encouraged
   to create new benchmarks patterned on these files.
