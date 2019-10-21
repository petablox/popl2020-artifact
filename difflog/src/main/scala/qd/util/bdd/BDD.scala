package qd.util.bdd

import qd.util.Contract

//noinspection ScalaUnnecessaryParentheses
sealed trait BDD[A <: Ordered[A]] extends ((A => Boolean) => Boolean) {

  def apply(v: A => Boolean): Boolean = this match {
    case Terminal(b) => b
    case Nonterminal(a, hi, lo) => if (v(a)) hi(v) else lo(v)
  }

  def firstVar: Option[A] = this match {
    case Terminal(_) => None
    case Nonterminal(a, _, _) => Some(a)
  }

  def &&(that: BDD[A]): BDD[A] = BDD.combine(this, that, _ && _)
  def ||(that: BDD[A]): BDD[A] = BDD.combine(this, that, _ || _)
  def !(): BDD[A] = BDD.negate2(this, Map[BDD[A], BDD[A]]())._1

}

object BDD {

  def apply[A <: Ordered[A]](a: A): BDD[A] = Nonterminal(a, Terminal(true), Terminal(false))

  def reduce[A <: Ordered[A]](bdd: BDD[A]): BDD[A] = reduce2(bdd, Set[BDD[A]]())._1
  def reduce2[A <: Ordered[A]](bdd: BDD[A], memo: Set[BDD[A]]): (BDD[A], Set[BDD[A]]) = bdd match {
    case Terminal(_) => (bdd, memo + bdd)
    case Nonterminal(a, hi, lo) =>
      val memo0 = memo
      val (rHi, memo1) = reduce2(hi, memo0)
      val (rLo, memo2) = reduce2(lo, memo1)
      var ans = if (rHi == rLo) rHi else Nonterminal(a, rHi, rLo)
      ans = memo2.find(_ == ans).getOrElse(ans)
      val memo3 = memo2 + ans
      (ans, memo3)
  }

  def negate2[A <: Ordered[A]](bdd: BDD[A], memo: Map[BDD[A], BDD[A]]): (BDD[A], Map[BDD[A], BDD[A]]) = {
    if (memo.contains(bdd)) (memo(bdd), memo)
    else bdd match {
      case Terminal(b) =>
        val ans: BDD[A] = Terminal(!b)
        (ans, memo + (bdd -> ans))
      case Nonterminal(a, hi, lo) =>
        val memo0 = memo
        val (aHi, memo1) = negate2(hi, memo0)
        val (aLo, memo2) = negate2(lo, memo1)
        val ans = Nonterminal(a, aHi, aLo)
        val memo3 = memo2 + (bdd -> ans)
        (ans, memo3)
    }
  }

  def combine[A <: Ordered[A]](bdd1: BDD[A], bdd2: BDD[A], op: (Boolean, Boolean) => Boolean): BDD[A] = {
    combine2(bdd1, bdd2, op, Map[(BDD[A], BDD[A]), BDD[A]]())._1
  }
  def combine2[A <: Ordered[A]](bdd1: BDD[A], bdd2: BDD[A], op: (Boolean, Boolean) => Boolean,
                                memo: Map[(BDD[A], BDD[A]), BDD[A]]): (BDD[A], Map[(BDD[A], BDD[A]), BDD[A]]) = {
    if (memo.contains((bdd1, bdd2))) (memo((bdd1, bdd2)), memo)
    else (bdd1, bdd2) match {
      case (Terminal(b1), Terminal(b2)) =>
        val ans: BDD[A] = Terminal(op(b1, b2))
        (ans, memo + ((bdd1, bdd2) -> ans))
      case (Nonterminal(a1, hi1, lo1), Terminal(_)) =>
        val memo0 = memo
        val (aHi, memo1) = combine2(hi1, bdd2, op, memo0)
        val (aLo, memo2) = combine2(lo1, bdd2, op, memo1)
        val ans = if (aHi != aLo) Nonterminal(a1, aHi, aLo) else aHi
        val memo3 = memo2 + ((bdd1, bdd2) -> ans)
        (ans, memo3)
      case (Terminal(_), Nonterminal(a2, hi2, lo2)) =>
        val memo0 = memo
        val (aHi, memo1) = combine2(bdd1, hi2, op, memo0)
        val (aLo, memo2) = combine2(bdd1, lo2, op, memo1)
        val ans = if (aHi != aLo) Nonterminal(a2, aHi, aLo) else aHi
        val memo3 = memo2 + ((bdd1, bdd2) -> ans)
        (ans, memo3)
      case (Nonterminal(a1, hi1, lo1), Nonterminal(a2, _, _)) if a1 < a2 =>
        val memo0 = memo
        val (aHi, memo1) = combine2(hi1, bdd2, op, memo0)
        val (aLo, memo2) = combine2(lo1, bdd2, op, memo1)
        val ans = if (aHi != aLo) Nonterminal(a1, aHi, aLo) else aHi
        val memo3 = memo2 + ((bdd1, bdd2) -> ans)
        (ans, memo3)
      case (Nonterminal(a1, hi1, lo1), Nonterminal(a2, hi2, lo2)) if a1 == a2 =>
        val memo0 = memo
        val (aHi, memo1) = combine2(hi1, hi2, op, memo0)
        val (aLo, memo2) = combine2(lo1, lo2, op, memo1)
        val ans = if (aHi != aLo) Nonterminal(a1, aHi, aLo) else aHi
        val memo3 = memo2 + ((bdd1, bdd2) -> ans)
        (ans, memo3)
      case (Nonterminal(a1, _, _), Nonterminal(a2, hi2, lo2)) if a1 > a2 =>
        val memo0 = memo
        val (aHi, memo1) = combine2(bdd1, hi2, op, memo0)
        val (aLo, memo2) = combine2(bdd2, lo2, op, memo1)
        val ans = if (aHi != aLo) Nonterminal(a1, aHi, aLo) else aHi
        val memo3 = memo2 + ((bdd1, bdd2) -> ans)
        (ans, memo3)
    }
  }

}

case class Terminal[A <: Ordered[A]](b: Boolean) extends BDD[A]
case class Nonterminal[A <: Ordered[A]](a: A, hi: BDD[A], lo: BDD[A]) extends BDD[A] {
  Contract.require(hi.firstVar.forall(_ > a))
  Contract.require(lo.firstVar.forall(_ > a))
}