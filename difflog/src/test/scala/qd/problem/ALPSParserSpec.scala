package qd
package problem

import org.scalatest.FunSuite

class ALPSParserSpec extends FunSuite {

  test("Simple PATH problem should produce expected numbers of relations and rules") {
    val dataStr = """V: 1,2,3,4,5,6,7.
                    |
                    |*edge(V,V)
                    |1,2
                    |2,3
                    |3,4
                    |4,5
                    |5,7
                    |5,6
                    |6,3
                    |.
                    |path(V,V)
                    |1,2
                    |1,3
                    |1,4
                    |1,5
                    |1,6
                    |1,7
                    |2,3
                    |2,4
                    |2,5
                    |2,6
                    |2,7
                    |3,3
                    |3,4
                    |3,5
                    |3,6
                    |3,7
                    |4,3
                    |4,4
                    |4,5
                    |4,6
                    |4,7
                    |5,3
                    |5,4
                    |5,5
                    |5,6
                    |5,7
                    |6,3
                    |6,4
                    |6,5
                    |6,6
                    |6,7
                    |.""".stripMargin
    val templateStr = """P0(v0,v1) :- P1(v0,v1).
                        |P0(v2,v1) :- P1(v0,v1),P2(v2,v0).""".stripMargin
    val problem = ALPSParser.parse(dataStr, templateStr)

    assert(problem.inputRels.map(_.name) == Set("edge"))
    assert(problem.inventedRels.map(_.name) == Set())
    assert(problem.outputRels.map(_.name) == Set("path"))

    assert(problem.rules.size == 5)

    assert(problem.discreteEDB.values.flatten.size == 7)
    assert(problem.discreteIDB.values.flatten.size == 31)
  }

}
