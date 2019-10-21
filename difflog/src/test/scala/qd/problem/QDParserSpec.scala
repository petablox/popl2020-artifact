package qd
package problem

import org.scalatest.FunSuite
import qd.data.graphs.Graphs

class QDParserSpec extends FunSuite {

  val node: Domain = Graphs.node
  val edge: Relation = Graphs.edge
  val nullRel: Relation = Relation("null", Vector())
  val path: Relation = Graphs.path
  val scc: Relation = Graphs.scc

  val a = Constant("a", node)
  val b = Constant("b", node)
  val c = Constant("c", node)
  val d = Constant("d", node)

  val v1 = Variable("v1", node)
  val v2 = Variable("v2", node)

  var ruleIndex = 0
  def weight(): (Token, FValue) = {
    val token = Token(s"R$ruleIndex")
    ruleIndex = ruleIndex + 1
    (token, FValue(0.2, token))
  }

  val allRulesRef: Set[Rule] = RuleEnumerator.enumerate(Set(edge), Set(path), Set(scc), 3, 4)

  val simpleInput1: String = """Input { edge(Node, Node), null() }
                              |Invented { path(Node, Node) }
                              |Output { scc(Node, Node) }
                              |EDB { edge(a, b), edge(b, c), edge(c, d), edge(d, a) }
                              |IDB { scc(a, b), scc(b, c) }
                              |Rules{
                              |  path(v1, v2) :- edge(v2, v1).
                              |  null() :- .
                              |}""".stripMargin

  test("Should parse simpleInput1") {
    val problem = new QDParser().parse(simpleInput1)

    assert(problem.inputRels == Set(edge, nullRel))
    assert(problem.inventedRels == Set(path))
    assert(problem.outputRels == Set(scc))

    val pedge = problem.edb(edge).support.map(tv => (tv._1, tv._2.v))
    assert(pedge.toSet == Set((DTuple(Vector(a, b)), 1.0),
                              (DTuple(Vector(b, c)), 1.0),
                              (DTuple(Vector(c, d)), 1.0),
                              (DTuple(Vector(d, a)), 1.0)))
    val pscc = problem.idb(scc).support.map(tv => (tv._1, tv._2.v))
    assert(pscc.toSet == Set((DTuple(Vector(a, b)), 1.0),
                             (DTuple(Vector(b, c)), 1.0)))

    assert(problem.rules.size == 2)
    problem.rules.find(rule => rule.head.relation == nullRel && rule.body.isEmpty).get
  }

  val simpleInput2: String = """Input { edge(Node, Node) }
                               |Invented { path(Node, Node) }
                               |Output { scc(Node, Node) }
                               |AllRules(3, 4)""".stripMargin

  test("Should parse simpleInput2") {
    val problem = new QDParser().parse(simpleInput2)

    assert(problem.inputRels == Set(edge))
    assert(problem.inventedRels == Set(path))
    assert(problem.outputRels == Set(scc))

    assert(!problem.edb.nonEmptySupport)
    assert(!problem.idb.nonEmptySupport)

    assert(problem.rules.size == allRulesRef.size)
  }

  val simpleInput3: String = """Input { edge(Node, Node) }
                               |Invented { path(Node, Node) }
                               |Output { scc(Node, Node) }
                               |AllRules(3, 4)""".stripMargin

  test("Should parse simpleInput3") {
    val problem = new QDParser().parse(simpleInput3)

    assert(problem.inputRels == Set(edge))
    assert(problem.inventedRels == Set(path))
    assert(problem.outputRels == Set(scc))

    assert(!problem.edb.nonEmptySupport)
    assert(!problem.idb.nonEmptySupport)

    assert(problem.rules.size == allRulesRef.size)
  }

  val commentedInput: String = """Input { edge(Node, Node), null() }
                                 |Invented { /* path(Node, Node, Node) */ path(Node, Node) }
                                 |Invented { }
                                 |Invented { // } path(Node)
                                 |}
                                 |Output { scc(Node, Node) }
                                 |Rules{
                                 |  path(v1, v2) :- edge(v2, v1).
                                 |}
                                 |EDB { edge(a, b), edge(b, c), edge(c, d), edge(a, c) }
                                 |IDB { scc(a, b), scc(b, c) }""".stripMargin

  test("Should parse the commented input") {
    val problem = new QDParser().parse(commentedInput)

    assert(problem.inputRels == Set(edge, Relation("null", Vector())))
    assert(problem.inventedRels == Set(path))
    assert(problem.outputRels == Set(scc))

    val pedge = problem.edb(edge).support.map(tv => (tv._1, tv._2.v))
    assert(pedge.toSet == Set((DTuple(Vector(a, b)), 1.0),
                              (DTuple(Vector(b, c)), 1.0),
                              (DTuple(Vector(c, d)), 1.0),
                              (DTuple(Vector(a, c)), 1.0)))
    val pscc = problem.idb(scc).support.map(tv => (tv._1, tv._2.v))
    assert(pscc.toSet == Set((DTuple(Vector(a, b)), 1.0),
                             (DTuple(Vector(b, c)), 1.0)))

    assert(problem.rules.size == 1)
    val prule = problem.rules.head
    assert(prule == Rule(prule.lineage, path(Vector(v1, v2)), Vector(edge(Vector(v2, v1)))))
  }

  val badInput1: String = """Input { edge(Node, Node),
                            |Invented { path(Node, Node) }
                            |Output { scc(Node, Node) }
                            |EDB { edge(a, b), edge(b, c), edge(c, d), edge(a, c) }
                            |IDB { path(a, b), path(b, c) }""".stripMargin

  test("Should fail to parse badInput1") {
    try {
      new QDParser().parse(badInput1)
      fail()
    } catch { case _: Throwable => () }
  }

  val badInput2: String = """Input { edge(Node, Node), edge() }
                           |Invented { path(Node, Node) }
                           |Output { scc(Node, Node) }
                           |EDB { edge(a, b), edge(b, c), edge(c, d), edge(a, c) }
                           |IDB { path(a, b), path(b, c) }""".stripMargin

  test("Should fail to parse badInput2") {
    try {
      new QDParser().parse(badInput2)
      fail()
    } catch { case _: Throwable => () }
  }

}
