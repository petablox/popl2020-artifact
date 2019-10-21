package qd
package dgraph

import qd.util.Contract

case class FatAssignment private (map: Map[Variable, Constant], antecedents: IndexedSeq[DTuple])
  extends (Variable => Constant) {
  Contract.deepRequire(map.forall { case (key, value) => key.domain == value.domain })

  override def apply(key: Variable): Constant = map(key)
  def get(key: Variable): Option[Constant] = map.get(key)
  def contains(key: Variable): Boolean = map.contains(key)

  def +(kv: (Variable, Constant)): FatAssignment = {
    val (key, value) = kv
    Contract.require(!map.contains(key))
    Contract.require(key.domain == value.domain)
    FatAssignment(map + kv, antecedents)
  }

  def addAntecedent(t: DTuple): FatAssignment = FatAssignment(map, antecedents :+ t)

  def toTuple(lit: Literal): DTuple = {
    val cs = lit.fields.map {
      case c @ Constant(_, _) => c
      case v @ Variable(_, _) => this(v)
    }
    DTuple(cs)
  }

  def toFilter(literal: Literal): IndexedSeq[Option[Constant]] = literal.fields.map {
    case v @ Variable(_, _) => map.get(v)
    case c @ Constant(_, _) => Some(c)
  }
}

object FatAssignment {
  val Empty: FatAssignment = FatAssignment(Map(), Vector())
}