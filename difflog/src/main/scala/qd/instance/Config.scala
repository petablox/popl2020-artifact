package qd
package instance

import qd.util.Contract

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configurations

case class Config[T <: Value[T]](map: Map[Relation, Instance[T]])(implicit vs: Semiring[T])
extends (Relation => Instance[T]) {
  Contract.require(map.forall { case (relation, instance) => relation.signature == instance.signature })

  override def apply(relation: Relation): Instance[T] = map.getOrElse(relation, Instance(relation))

  def map[U <: Value[U]](f: T => U)(implicit us: Semiring[U]): Config[U] = {
    Config(map.map { case (rel, inst) => rel -> inst.map(f) })
  }

  def add(relation: Relation, tuple: DTuple, value: T): Config[T] = {
    val newInstance = this(relation) + (tuple -> value)
    Config(map + (relation -> newInstance))
  }

  def nonEmptySupport: Boolean = map.values.exists(_.nonEmpty)
}

object Config {
  def apply[T <: Value[T]](firstPair: (Relation, Instance[T]), remainingPairs: (Relation, Instance[T])*)
                          (implicit vs: Semiring[T]): Config[T] = {
    Config((firstPair +: remainingPairs).toMap)
  }
  def apply[T <: Value[T]]()(implicit vs: Semiring[T]): Config[T] = Config[T](Map[Relation, Instance[T]]())

  def reposition(config: Config[FValue], newPos: Token => FValue): Config[FValue] = {
    Config(config.map.map { case (rel, instance) => rel -> Instance.reposition(instance, newPos) })
  }
}
