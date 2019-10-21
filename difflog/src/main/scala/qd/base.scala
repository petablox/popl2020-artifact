package qd

import qd.util.Contract

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Domains, Parameters, Constants, and Variables

case class Domain(name: Any) {
  override def toString: String = s"$name"
  override val hashCode: Int = ("D", name).hashCode()
}

sealed abstract class Parameter {
  def name: Any
  def domain: Domain
  override def toString: String = s"$name"
}
case class Constant(name: Any, domain: Domain) extends Parameter {
  override val hashCode: Int = ("C", name, domain).hashCode()
}
case class Variable(name: Any, domain: Domain) extends Parameter {
  override val hashCode: Int = ("V", name, domain).hashCode()
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Relations and Tuples

case class Relation(name: Any, signature: IndexedSeq[Domain]) {
  def arity: Int = signature.length
  def apply(fields: IndexedSeq[Parameter]): Literal = Literal(this, fields)
  override def toString: String = s"$name(${signature.mkString(", ")})"
  override val hashCode: Int = ("R", name, signature).hashCode()
}

case class DTuple(fields: IndexedSeq[Constant]) extends IndexedSeq[Constant] {
  lazy val signature: IndexedSeq[Domain] = fields.map(_.domain)
  def arity: Int = fields.length

  override def apply(index: Int): Constant = fields(index)
  override def length: Int = fields.length
  override val hashCode: Int = fields.hashCode()
  override def head: Constant = fields.head
  override def tail: DTuple = DTuple(fields.tail)

  def +:(field: Constant): DTuple = DTuple(field +: fields)
  def :+(field: Constant): DTuple = DTuple(fields :+ field)

  override def toString: String = fields.mkString("(", ", ", ")")
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Literals and Rules

case class Literal(relation: Relation, fields: IndexedSeq[Parameter]) {
  Contract.require(relation.signature == fields.map(_.domain))
  val variables: Set[Variable] = fields.collect({ case v: Variable => v }).toSet
  override def toString: String = s"${relation.name}(${fields.mkString(", ")})"

  def rename(f: Variable => Variable): Literal = Literal(relation, fields.map {
    case v @ Variable(_, _) => f(v)
    case c @ Constant(_, _) => c
  })
}

case class Rule(lineage: Lineage, head: Literal, body: IndexedSeq[Literal]) {
  val variables: Set[Variable] = body.flatMap(_.variables).toSet
  Contract.require(head.variables.subsetOf(variables))

  override def toString: String = {
    val sortedBody = body.map(_.toString)
    s"$lineage: $head :- ${sortedBody.mkString(", ")}."
  }

  lazy val valency: Int = Rule.valency(head, body)

  lazy val normalized: Rule = {
    val renamingMap = scala.collection.mutable.Map[Variable, Variable]()
    def rename(vOld: Variable): Variable = {
      if (!renamingMap.contains(vOld)) {
        val index = Stream.from(0).find(idx => renamingMap.values.count(_.name == s"v$idx") == 0).get
        renamingMap.put(vOld, Variable(s"v$index", vOld.domain))
      }
      renamingMap(vOld)
    }

    val ansBody0 = body.distinct
    val ansBody1 = ansBody0.permutations.minBy(vec => (Rule.valency(head, vec), vec.toString))
    val ansBody2 = for (literal <- ansBody1)
                   yield {
                     val newFields = literal.fields.map {
                       case v @ Variable(_, _) => rename(v)
                       case p @ Constant(_, _) => p
                     }
                     Literal(literal.relation, newFields)
                   }
    val ansHead = head.rename(rename)

    Rule(lineage, ansHead, ansBody2)
  }
}

object Rule {

  def valency(head: Literal, body: IndexedSeq[Literal]): Int = Range(0, 1 + body.size).map({ i =>
    val left = body.take(i)
    val right = body.drop(i) :+ head
    val leftVars = left.flatMap(_.variables).toSet
    val rightVars = right.flatMap(_.variables).toSet
    leftVars.intersect(rightVars).size
  }).max

}
