package qd.util

class Multiset[A](val map: Map[A, Int]) extends (A => Int) {
  Contract.require(map.values.forall(_ > 0))

  override def apply(a: A): Int = map.getOrElse(a, 0)
  def support: Set[A] = map.keySet

  def +(a: A): Multiset[A] = new Multiset(map + (a -> (1 + this(a))))

  def ++(that: Multiset[A]): Multiset[A] = {
    val newMap = for (a <- this.map.keySet ++ that.map.keySet;
                      thisVal = this(a);
                      thatVal = that(a))
                 yield a -> (thisVal + thatVal)
    new Multiset(newMap.toMap)
  }

  override def equals(obj: Any): Boolean = obj match {
    case that: Multiset[A] => this.map == that.map
    case _ => false
  }

  override def hashCode(): Int = map.hashCode()

  override def toString(): String = {
    val elems = map.map({ case (a, freq) => s"$a: $freq" })
    elems.mkString("Multiset(", ", ", ")")
  }
}

object Multiset {
  def apply[A](): Multiset[A] = new Multiset(Map())
}
