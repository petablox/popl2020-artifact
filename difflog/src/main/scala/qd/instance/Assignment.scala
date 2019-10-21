package qd
package instance

import qd.util.Contract

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Assignments

case class Assignment[T <: Value[T]] private (map: Map[Variable, Constant], score: T) extends (Variable => Constant) {
  Contract.deepRequire(map.forall { case (key, value) => key.domain == value.domain })

  override def apply(key: Variable): Constant = map(key)
  def get(key: Variable): Option[Constant] = map.get(key)
  def contains(key: Variable): Boolean = map.contains(key)

  def +(kv: (Variable, Constant)): Assignment[T] = {
    val (key, value) = kv
    Contract.require(!map.contains(key))
    Contract.require(key.domain == value.domain)
    Assignment(map + kv, score)
  }
  def *(coeff: T): Assignment[T] = Assignment(map, score * coeff)

  def project(rvs: Set[Variable]): Assignment[T] = Assignment(map.filterKeys(rvs), score)

  def toTuple(lit: Literal): (DTuple, T) = {
    val cs = lit.fields.map {
      case c @ Constant(_, _) => c
      case v @ Variable(_, _) => this(v)
    }
    (DTuple(cs), score)
  }

  def toFilter(literal: Literal): IndexedSeq[Option[Constant]] = literal.fields.map {
    case v @ Variable(_, _) => map.get(v)
    case c @ Constant(_, _) => Some(c)
  }
}

object Assignment {
  def Empty[T <: Value[T]]()(implicit vs: Semiring[T]): Assignment[T] = Assignment(Map(), vs.One)
}
