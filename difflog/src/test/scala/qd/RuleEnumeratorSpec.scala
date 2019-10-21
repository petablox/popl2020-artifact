package qd

import org.scalatest.FunSuite
import data.graphs.Graphs

import scala.util.Random

class RuleEnumeratorSpec extends FunSuite {

  val edge: Relation = Graphs.edge
  val path: Relation = Graphs.path
  val scc: Relation = Graphs.scc

  val rng: Random = new Random(0)
  var ruleIndex = 0

  def weight(): (Token, FValue) = {
    val token = Token(s"R$ruleIndex")
    ruleIndex = ruleIndex + 1
    val value = rng.nextDouble()
    (token, FValue(value, token))
  }

  val s: Set[Relation] = Set()
  val se: Set[Relation] = Set(edge)
  val sp: Set[Relation] = Set(path)
  val ss: Set[Relation] = Set(scc)
  
  val memo: Set[(Set[Relation], Set[Relation], Set[Relation], Int, Int, Int)] = Set((se, s, ss, 0, 0, 0),
                                                                                    (se, s, ss, 0, 1, 0),
                                                                                    (se, s, ss, 0, 2, 0),
                                                                                    (se, s, ss, 0, 3, 0),

                                                                                    (se, s, ss, 1, 0, 0),
                                                                                    (se, s, ss, 1, 1, 1),
                                                                                    (se, s, ss, 1, 2, 8),
                                                                                    (se, s, ss, 1, 3, 8),

                                                                                    (se, sp, ss, 0, 0, 0),
                                                                                    (se, sp, ss, 0, 1, 0),
                                                                                    (se, sp, ss, 0, 2, 0),
                                                                                    (se, sp, ss, 0, 3, 0),

                                                                                    (se, sp, ss, 1, 0, 0),
                                                                                    (se, sp, ss, 1, 1, 4),
                                                                                    (se, sp, ss, 1, 2, 26),
                                                                                    (se, sp, ss, 1, 3, 26),

                                                                                    (se, sp, ss, 3, 4, 19238))

  test("Should enumerate expected number of rules") {
    for ((edbRels, invRels, idbRels, maxLiterals, maxVars, expSize) <- memo) {
      val rules = RuleEnumerator.enumerate(edbRels, invRels, idbRels, maxLiterals, maxVars)
      lazy val caseName = s"${edbRels.map(_.name)}, ${invRels.map(_.name)}, ${idbRels.map(_.name)}, " +
                          s"$maxLiterals, $maxVars, $expSize"
      assert(rules.size == expSize, s"(Case $caseName)")
    }
  }

  test("Should contain the usual suspects") {
    val allRules = RuleEnumerator.enumerate(se, sp, ss, 3, 4)
                                 .map(r => Rule(Token("R"), r.head, r.body))
    val baseSpec = new BaseSpec
    for (rule <- Set(baseSpec.rule1, baseSpec.rule2, baseSpec.rule3, baseSpec.rule4, baseSpec.rule5, baseSpec.rule6)) {
      assert(allRules.contains(Rule(Token("R"), rule.head, rule.body).normalized))
    }
  }

}
