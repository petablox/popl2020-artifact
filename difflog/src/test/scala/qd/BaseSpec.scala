package qd

import org.scalatest.FunSuite
import qd.data.graphs.Graphs._

class BaseSpec extends FunSuite {

  val vs: Semiring[FValue] = implicitly[Semiring[FValue]]

  val u = Variable("u", node)
  val v = Variable("v", node)
  val w = Variable("w", node)
  val x = Variable("x", node)
  val y = Variable("y", node)
  val z = Variable("z", node)

  val rule1 = Rule(Token(1), Literal(path, Vector(u, v)),
                             Vector(Literal(edge, Vector(u, v))))
  val rule2 = Rule(Token(2), Literal(path, Vector(x, u)),
                             Vector(Literal(edge, Vector(x, u))))
  val rule3 = Rule(Token(3), Literal(path, Vector(u, v)),
                             Vector(Literal(edge, Vector(v, u))))
  val rule4 = Rule(Token(4), Literal(path, Vector(u, w)),
                             Vector(Literal(edge, Vector(u, v)),
                                    Literal(edge, Vector(v, w))))
  val rule5 = Rule(Token(5), Literal(path, Vector(u, w)),
                             Vector(Literal(edge, Vector(v, w)),
                                    Literal(edge, Vector(u, v))))
  val rule6 = Rule(Token(6), Literal(path, Vector(u, x)),
                             Vector(Literal(edge, Vector(u, v)),
                                    Literal(edge, Vector(w, x)),
                                    Literal(edge, Vector(v, w))))

  test("Valencies should be correctly computed") {
    assert(rule1.valency == 2)
    assert(rule2.valency == 2)
    assert(rule3.valency == 2)
    assert(rule4.valency == 2)
    assert(rule5.valency == 2)
    assert(rule6.valency == 4)
    assert(rule6.normalized.valency == 2)
  }

  test("Normalization is idempotent") {
    for (rule <- Set(rule1, rule2, rule3, rule4, rule5, rule6)) {
      assert(rule.normalized.normalized == rule.normalized)
    }
  }

  def rename(rule: Rule): Rule = Rule(Token("R"), rule.head, rule.body)

  test("Normalization preserves variable names") {
    assert(rename(rule1.normalized) == rename(rule2.normalized))
    assert(rule1 != rule2 && rename(rule1) != rename(rule2))
    assert(rule1.normalized != rule3.normalized && rename(rule1.normalized) != rename(rule3.normalized))
  }

  test("Normalization recovers some rule identities") {
    assert(rename(rule4.normalized) == rename(rule5.normalized))
  }

}
