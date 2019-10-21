package qd
package instance

import org.scalatest.FunSuite

import scala.collection.immutable.Seq

class InstanceSpec extends FunSuite {

  val alphabet = Domain(classOf[Character])
  val digit = Domain(classOf[Int])

  val a = Constant('a', alphabet)
  val b = Constant('b', alphabet)
  val c = Constant('c', alphabet)

  val d0 = Constant(0, digit)
  val d1 = Constant(1, digit)
  val d2 = Constant(2, digit)

  val ad0 = DTuple(Vector(a, d0))
  val ad1 = DTuple(Vector(a, d1))
  val abd0 = DTuple(Vector(a, b, d0))
  val cbd0 = DTuple(Vector(c, b, d0))

  val f1 = FValue(0.3, Empty)
  val f2 = FValue(0.25, Empty)
  val f12: FValue = f1 + f2

  val instAD1: Instance[FValue] = Instance(Vector(alphabet, digit))
  val instAD2: Instance[FValue] = instAD1 + (ad0 -> f1)

  val instAAD1: Instance[FValue] = Instance(Vector(alphabet, alphabet, digit))
  val instAAD2: Instance[FValue] = instAAD1 + (abd0 -> f2)
  val instAAD3: Instance[FValue] = instAAD2 + (abd0 -> f1)
  val instAAD4: Instance[FValue] = instAAD2 + (cbd0 -> f12)

  test("Signatures are computed correctly") {
    assert(instAD1.signature == Seq(alphabet, digit))
    assert(instAD2.signature == Seq(alphabet, digit))

    assert(instAAD1.signature == Seq(alphabet, alphabet, digit))
    assert(instAAD2.signature == Seq(alphabet, alphabet, digit))
    assert(instAAD3.signature == Seq(alphabet, alphabet, digit))
    assert(instAAD4.signature == Seq(alphabet, alphabet, digit))
  }

  test("Supports are computed correctly") {
    assert(instAD1.support.toSet == Set())
    assert(instAD2.support.toSet == Set((ad0, f1)))

    assert(instAAD1.support.toSet == Set())
    assert(instAAD2.support.toSet == Set((abd0, f2)))
    assert(instAAD3.support.toSet == Set((abd0, f12)))
    assert(instAAD4.support.toSet == Set((abd0, f2), (cbd0, f12)))
  }

  test("Instance emptiness check works as desired") {
    assert(instAD1.isEmpty)
    assert(instAD2.nonEmpty)

    assert(instAAD1.isEmpty)
    assert(instAAD2.nonEmpty)
    assert(instAAD3.nonEmpty)
    assert(instAAD4.nonEmpty)
  }

  test("Values are retrieved correctly") {
    val vs = implicitly[Semiring[FValue]]
    assert(instAD1(ad0) == vs.Zero)
    assert(instAD1(ad1) == vs.Zero)

    assert(instAD2(ad0) == f1)
    assert(instAD2(ad1) == vs.Zero)
  }

  test("Instances are filtered correctly") {
    def fmatch(f: Seq[Option[Constant]], t: IndexedSeq[Constant]): Boolean = {
      require(f.length == t.length, s"$f, $t")
      if (f.nonEmpty) {
        val fhead = f.head
        val thead = t.head
        if (fhead.nonEmpty) fhead.get == thead && fmatch(f.tail, t.tail)
        else fmatch(f.tail, t.tail)
      } else true
    }

    for (inst <- Set(instAD1, instAD2);
         f <- Set(Vector(None, None),
                  Vector(Some(a), None),
                  Vector(Some(b), None),
                  Vector(Some(a), Some(b)),
                  Vector(None, Some(c)))) {
      assert(inst.filter(f).toSet == inst.support.filter({ case (tuple, _) => fmatch(f, tuple) }).toSet)
    }

    for (inst <- Set(instAAD1, instAAD2, instAAD3, instAAD4);
         f <- Set(Vector(None, None, None),
                  Vector(Some(a), None, Some(d0)),
                  Vector(Some(b), Some(c), Some(d1)),
                  Vector(Some(a), Some(b), None),
                  Vector(None, Some(c), Some(d2)))) {
      assert(inst.filter(f).toSet == inst.support.filter({ case (tuple, _) => fmatch(f, tuple) }).toSet)
    }
  }

  test("Tuples are correctly added to instances") {
    assert(instAD1 + (ad1 -> f2) + (ad0 -> f1) == instAD2 + (ad1 -> f2))
    assert(instAD2 + (ad0 -> f1) == instAD2)
    assert(instAD1 + (ad0 -> f2) + (ad0 -> f1) == instAD2)
  }

}
