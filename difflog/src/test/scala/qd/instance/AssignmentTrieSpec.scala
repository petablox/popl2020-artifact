package qd
package instance

import org.scalatest.FunSuite
import qd.Semiring.FValueSemiringObj
import qd.data.graphs.Graphs

class AssignmentTrieSpec extends FunSuite {

  val node: Domain = Graphs.node

  val a: Constant = Constant("a", node)
  val b: Constant = Constant("b", node)
  val c: Constant = Constant("c", node)

  val v: IndexedSeq[Variable] = Range(0, 3).map(i => Variable(s"v$i", node))

  implicit val ordering: Ordering[Variable] = (x: Variable, y: Variable) => {
    val ix = v.indexOf(x)
    val iy = v.indexOf(y)
    implicitly[Ordering[Int]].compare(ix, iy)
  }

  implicit val vs: Semiring[FValue] = FValueSemiringObj

  val asgn0: AssignmentTrie[FValue] = AssignmentTrie()

  val asgn1: AssignmentTrie[FValue] = AssignmentTrie(Vector(v(0), v(1), v(2)),
                                                     Instance[FValue](Vector(node, node, node)) +
                                                     (DTuple(Vector(a, b, c)) -> FValue(0.2, Empty)) +
                                                     (DTuple(Vector(a, c, c)) -> FValue(0.3, Empty)) +
                                                     (DTuple(Vector(b, b, c)) -> FValue(0.5, Empty)) +
                                                     (DTuple(Vector(b, a, c)) -> FValue(0.1, Empty)) +
                                                     (DTuple(Vector(b, c, c)) -> FValue(0.4, Empty)))

  val asgn2: AssignmentTrie[FValue] = AssignmentTrie(Vector(v(0), v(2)),
                                                     Instance[FValue](Vector(node, node)) +
                                                     (DTuple(Vector(a, c)) -> FValue(0.3, Empty)) +
                                                     (DTuple(Vector(b, c)) -> FValue(0.5, Empty)))

  val asgn3: AssignmentTrie[FValue] = AssignmentTrie(Vector(v(1), v(2)),
                                                     Instance[FValue](Vector(node, node)) +
                                                     (DTuple(Vector(b, c)) -> FValue(0.2, Empty)) +
                                                     (DTuple(Vector(b, b)) -> FValue(0.5, Empty)))

  val asgn4: AssignmentTrie[FValue] = AssignmentTrie(Vector(v(0), v(1), v(2)),
                                                     Instance[FValue](Vector(node, node, node)) +
                                                     (DTuple(Vector(a, b, c)) -> FValue(0.06, Empty)) +
                                                     (DTuple(Vector(b, b, c)) -> FValue(0.10, Empty)))

  val lit1: Literal = Literal(Relation("R3", Vector(node, node,node)), Vector(v(2), v(2), v(1)))
  val lit2: Literal = Literal(Relation("R3", Vector(node, node,node)), Vector(v(1), v(1), v(2)))

  val inst1: Instance[FValue] = Instance[FValue](Vector(node, node, node)) +
                                (DTuple(Vector(b, b, c)) -> FValue(0.2, Empty)) +
                                (DTuple(Vector(c, c, c)) -> FValue(0.3, Empty)) +
                                (DTuple(Vector(b, b, c)) -> FValue(0.5, Empty)) +
                                (DTuple(Vector(a, a, c)) -> FValue(0.1, Empty)) +
                                (DTuple(Vector(c, c, c)) -> FValue(0.4, Empty))

  val asgn5: AssignmentTrie[FValue] = AssignmentTrie(Vector(v(1), v(2)),
                                                     Instance[FValue](Vector(node, node)) +
                                                     (DTuple(Vector(c, b)) -> FValue(0.2, Empty)) +
                                                     (DTuple(Vector(c, c)) -> FValue(0.3, Empty)) +
                                                     (DTuple(Vector(c, b)) -> FValue(0.5, Empty)) +
                                                     (DTuple(Vector(c, a)) -> FValue(0.1, Empty)) +
                                                     (DTuple(Vector(c, c)) -> FValue(0.4, Empty)))

  test("Assignments should be correctly constructed") {
    assert(AssignmentTrie(inst1.support, lit1) == asgn5)
  }

  test("Assignments should be correctly grounded") {
    val a1inst = asgn1.support.map(_.toTuple(lit2)).foldLeft(Instance(inst1.signature))(_ + _)
    assert(a1inst.support.toSet == inst1.support.toSet)
  }

  test("Joins should be correctly computed") {
    assert(AssignmentTrie.join(asgn0, asgn2) == asgn2)
    assert(AssignmentTrie.join(asgn2, asgn0) == asgn2)

    val asgn23 = AssignmentTrie.join(asgn2, asgn3)
    assert(asgn23.signature == asgn4.signature)
    for ((t, v23) <- asgn23.instance.support) {
      assert(asgn4.instance(t).v == v23.v)
    }
  }

  test("Project should retain correct assignments") {
    assert(AssignmentTrie.project(asgn1, Set(v(0), v(2))) == asgn2)
  }

}
