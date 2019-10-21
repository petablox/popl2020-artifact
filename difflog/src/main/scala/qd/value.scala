package qd

import qd.util.Contract

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Values

// Note that values only form a pre-order! Not even a partial order!
// In particular, a <~ b and b <~ a does not imply a == b
// For example, consider the case of lineages l1 != l2, and FValue(0.8, l1) and FValue(0.8, l2)
trait Value[T <: Value[T]] {
  def +(that: T): T
  def *(that: T): T
  def <~(that: T): Boolean
  def >~(that: T): Boolean = that <~ this.unwrap
  def <(that: T): Boolean = this <~ that && !(that <~ this.unwrap)
  def >(that: T): Boolean = that <~ this.unwrap && !(this <~ that)
  def unwrap: T
}

object Value {
  def apply[T <: Value[T]](l: Lineage, f: Token => T)(implicit vs: Semiring[T]): T = l match {
    case Empty => vs.One
    case t @ Token(_) => f(t)
    case And(l1, l2) => Value(l1, f) * Value(l2, f)
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Semirings

trait Semiring[T <: Value[T]] {
  def One: T
  def Zero: T
  def nonZero(t: T): Boolean
}

object Semiring {
  implicit object BValueSemiringObj extends BValueSemiring
  implicit object FValueSemiringObj extends FValueSemiring
  implicit object DValueSemiringObj extends DValueSemiring
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Boolean Values

sealed abstract class BValue extends Value[BValue] {
  override def +(that: BValue): BValue = (this, that) match {
    case (BFalse, BFalse) => BFalse
    case _ => BTrue
  }
  override def *(that: BValue): BValue = (this, that) match {
    case (BTrue, BTrue) => BTrue
    case _ => BFalse
  }
  override def <~(that: BValue): Boolean = (this, that) match {
    case (BTrue, BFalse) => false
    case _ => true
  }
  override def unwrap: BValue = this
}

case object BTrue extends BValue
case object BFalse extends BValue

class BValueSemiring extends Semiring[BValue] {
  override def One: BValue = BTrue
  override def Zero: BValue = BFalse
  override def nonZero(t: BValue): Boolean = t == BTrue
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Viterbi Values

case class FValue(v: Double, l: Lineage) extends Value[FValue] {
  Contract.require(0.0 <= v && v <= 1.0, s"Initializing FValue with value $v")
  override def +(that: FValue): FValue = if (this <~ that) that else this
  override def *(that: FValue): FValue = FValue(this.v * that.v, this.l * that.l)
  override def <~(that: FValue): Boolean = this.v <= that.v
  override def unwrap: FValue = this
  override def toString: String = s"$v"
}

class FValueSemiring extends Semiring[FValue] {
  override val One: FValue = FValue(1.0, Empty)
  override val Zero: FValue = FValue(0.0, Empty)
  override def nonZero(t: FValue): Boolean = t.v > 0.0
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Full Provenance Values

class DValue private (val r: Set[Set[Token]]) extends Value[DValue] {
  override def +(that: DValue): DValue = DValue(this.r ++ that.r)
  override def *(that: DValue): DValue = DValue(for (s1 <- this.r; s2 <- that.r) yield s1 ++ s2)
  override def <~(that: DValue): Boolean = this.r.forall(s1 => that.r.exists(s2 => s2.subsetOf(s1)))
  override def unwrap: DValue = this

  override def equals(obj: Any): Boolean = obj match {
    case d: DValue => r == d.r
    case _ => false
  }
  override def hashCode(): Int = r.hashCode()
}

object DValue {
  def canonicalize(r: Set[Set[Token]]): Set[Set[Token]] = {
    for (s <- r; if r.filter(_ != s).forall(!_.subsetOf(s))) yield s
  }
  def apply(r: Set[Set[Token]]): DValue = new DValue(canonicalize(r))
}

class DValueSemiring extends Semiring[DValue] {
  override def One: DValue = DValue(Set(Set()))
  override def Zero: DValue = DValue(Set())
  override def nonZero(t: DValue): Boolean = t.r.nonEmpty
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vectors of Values

case class VecValue[T <: Value[T]](vec: IndexedSeq[T]) extends Value[VecValue[T]] {
  Contract.require(vec.nonEmpty)
  override def +(that: VecValue[T]): VecValue[T] = {
    Contract.require(vec.size == that.vec.size)
    VecValue(vec.zip(that.vec).map { case (v1, v2) => v1 + v2 })
  }
  override def *(that: VecValue[T]): VecValue[T] = {
    Contract.require(vec.size == that.vec.size)
    VecValue(vec.zip(that.vec).map { case (v1, v2) => v1 * v2 })
  }
  override def <~(that: VecValue[T]): Boolean = {
    Contract.require(vec.size == that.vec.size)
    vec.zip(that.vec).forall { case (v1, v2) => v1 <~ v2 }
  }
  override def unwrap: VecValue[T] = this
  override def toString: String = s"VecValue(${vec.mkString(", ")})"
}

case class VecValueSemiring[T <: Value[T]](n: Int)(implicit vs: Semiring[T]) extends Semiring[VecValue[T]] {
  Contract.require(n > 0)
  override def One: VecValue[T] = VecValue(Range(0, n).map(_ => vs.One))
  override def Zero: VecValue[T] = VecValue(Range(0, n).map(_ => vs.Zero))
  override def nonZero(t: VecValue[T]): Boolean = t.vec.exists(vs.nonZero)
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Coprovenance

case class Coprov(set: Set[Token]) extends Value[Coprov] {
  override def +(that: Coprov): Coprov = Coprov(this.set & that.set)
  override def *(that: Coprov): Coprov = Coprov(this.set | that.set)
  override def <~(that: Coprov): Boolean = that.set.forall(this.set)
  override def unwrap: Coprov = this
}

case class CoprovSemiring(allTokens: Set[Token]) extends Semiring[Coprov] {
  override val One: Coprov = Coprov(Set.empty)
  override val Zero: Coprov = Coprov(allTokens)
  override def nonZero(t: Coprov): Boolean = t.set.nonEmpty
}
