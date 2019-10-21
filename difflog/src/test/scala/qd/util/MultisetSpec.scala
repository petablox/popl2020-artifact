package qd.util

import org.scalatest.FunSuite

import scala.collection.immutable.{HashMap, TreeMap}

class MultisetSpec extends FunSuite {
  val m0: Multiset[Char] = Multiset()
  val m1 = new Multiset(HashMap('a' -> 3, 'b' -> 1))
  val m2 = new Multiset(TreeMap('a' -> 3, 'b' -> 1))
  val m3 = new Multiset(Map('a' -> 2, 'b' -> 1))

  test("Multiset counts are retrieved correctly") {
    assert(m0('a') == 0)
    assert(m0('b') == 0)
    assert(m0('c') == 0)

    assert(m1('a') == 3)
    assert(m1('b') == 1)
    assert(m1('c') == 0)

    assert(m2('a') == 3)
    assert(m2('b') == 1)
    assert(m2('c') == 0)

    assert(m3('a') == 2)
    assert(m3('b') == 1)
    assert(m3('c') == 0)
  }

  test("Individual elements are correctly added to multisets") {
    val m4 = m3 + 'a' + 'c'
    assert(m4('a') == m3('a') + 1)
    assert(m4('b') == m3('b'))
    assert(m4('c') == m3('c') + 1)
  }

  test("The union of multisets is computed correctly") {
    val m4 = m1 ++ m3
    assert(m4('a') == m1('a') + m3('a'))
    assert(m4('b') == m1('b') + m3('b'))
    assert(m4('c') == m1('c') + m3('c'))
  }

  test("Multisets respect equality, regardless of the underlying map implementation") {
    assert(m1 == m2)
    assert(m1 != m3)
    assert(m1 == m3 + 'a')
    assert(m3 == m0 + 'a' + 'a' + 'b')
  }

  test("Multiset supports are determined correctly") {
    assert(m0.support == Set())
    assert(m1.support == Set('a', 'b'))
    assert(m2.support == Set('a', 'b'))
    assert(m3.support == Set('a', 'b'))
    assert((m1 + 'a').support == Set('a', 'b'))
    assert((m1 + 'b').support == Set('a', 'b'))
    assert((m1 + 'c').support == Set('a', 'b', 'c'))
  }
}
