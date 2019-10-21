#!/usr/bin/env bash

set -e

sbt-test() {
  sbt "testOnly $1"
}

sbt-test qd.BaseSpec
sbt-test qd.RuleEnumeratorSpec

sbt-test qd.instance.InstanceSpec
sbt-test qd.instance.AssignmentTrieSpec

sbt-test qd.evaluator.NaiveEvaluatorSpec
sbt-test qd.evaluator.SeminaiveEvaluatorSpec
sbt-test qd.evaluator.TrieEvaluatorSpec
sbt-test qd.evaluator.TrieSemiEvaluatorSpec
sbt-test qd.evaluator.TrieJoinEvaluatorSpec

sbt-test qd.learner.NewtonRootLearnerSpec

echo "Done!"
