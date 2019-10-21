package qd
package instance

import qd.util.{Contract, Timers}

case class AssignmentTrie[T <: Value[T]](signature: IndexedSeq[Variable], instance: Instance[T])
                                        (implicit vs: Semiring[T], ordering: Ordering[Variable]) {

  Contract.deepRequire(Range(0, signature.size - 1).forall(i => ordering.lt(signature(i), signature(i + 1))))
  Contract.deepRequire(signature.map(_.domain) == instance.signature)
  def *(t: T): AssignmentTrie[T] = AssignmentTrie(signature, instance * t)

  lazy val support: Vector[Assignment[T]] = Timers("AssignmentTrie.support") {
    def _support(_signature: IndexedSeq[Variable], _instance: Instance[T]): Vector[Assignment[T]] = {
      if (_signature.isEmpty) {
        val InstanceBase(value) = _instance
        if (vs.nonZero(value)) Vector(Assignment(Map(), value)) else Vector()
      } else {
        val vHead = _signature.head
        val subSignature = _signature.tail
        val InstanceInd(_, _, map) = _instance
        for ((cHead, subInstance) <- map.toVector; subAssignment <- _support(subSignature, subInstance))
        yield subAssignment + (vHead -> cHead)
      }
    }
    _support(signature, instance)
  }

  def toTuples(head: Literal): IndexedSeq[(DTuple, T)] = Timers("AssignmentTrie.toTuples") {
    // We are going to recurse over the structure of the AssignmentTrie.
    // At each level, we will encounter (variable -> constant) assignments.
    // We need to know into which fields of the result to place this constant.

    // val headIndexed = head.fields.zipWithIndex
    // val plan = for (v <- signature) yield headIndexed.filter(_._1 == v).map(_._2)

    val headIndexed = head.fields.zipWithIndex.groupBy(_._1)
    val plan = for (v <- signature) yield headIndexed.getOrElse(v, Vector()).map(_._2)

    // WARNING: RawTuples are mutable, and should not be exported outside this function.
    type RawTuple = Array[Option[Constant]]
    def rawToDTuple(t: RawTuple): DTuple = DTuple(t.map(_.get))
    val seed = for (f <- head.fields)
               yield f match {
                 case c @ Constant(_, _) => Some(c)
                 case Variable(_, _) => None
               }

    def _toTuples(
                   _plan: IndexedSeq[IndexedSeq[Int]],
                   _instance: Instance[T]
                 ): IndexedSeq[(RawTuple, T)] = {
      if (_plan.isEmpty) {
        val InstanceBase(value) = _instance
        if (vs.nonZero(value)) Vector((seed.toArray, value)) else Vector()
      } else {
        val pHead = _plan.head
        val subPlan = _plan.tail
        val InstanceInd(_, _, map) = _instance

        // The tuple t is updated in place
        def extendRawTuple(t: RawTuple, cHead: Constant): Unit = {
          val scHead = Some(cHead)
          for (index <- pHead) {
            t(index) = scHead
          }
        }

        for ((cHead, subInstance) <- map.toVector;
             (t, v) <- _toTuples(subPlan, subInstance))
        yield {
          extendRawTuple(t, cHead)
          (t, v)
        }
      }
    }

    _toTuples(plan, instance).map { case (t, v) => (rawToDTuple(t), v) }
  }

}

object AssignmentTrie {

  def apply[T <: Value[T]]()(implicit ordering: Ordering[Variable], vs: Semiring[T]): AssignmentTrie[T] = {
    AssignmentTrie(Vector(), InstanceBase(vs.One))
  }

  def apply[T <: Value[T]](support: Seq[(DTuple, T)], literal: Literal)
                          (implicit ordering: Ordering[Variable], vs: Semiring[T]): AssignmentTrie[T] = {
    val allVars = literal.fields.collect({ case v @ Variable(_, _) => v }).sorted.distinct
    val varIndex = allVars.zipWithIndex.toMap

    def shuffle(t: DTuple): Option[DTuple] = {
      Contract.assert(literal.fields.size == t.length)
      var success = true
      val ans: Array[Option[Constant]] = Array.fill(allVars.size)(None)
      for (i <- Range(0, t.length)) {
        literal.fields(i) match {
          case c @ Constant(_, _) => if (t(i) != c) { success = false }
          case v @ Variable(_, _) if ans(varIndex(v)).isEmpty => ans(varIndex(v)) = Some(t(i))
          case v @ Variable(_, _) => if (t(i) != ans(varIndex(v)).get) { success = false }
        }
      }
      if (success) Some(DTuple(ans.map(_.get).toVector)) else None
    }

    val shuffledSupport = for ((t, v) <- support; ost = shuffle(t) if ost.nonEmpty) yield (ost.get, v)

    val ansSignature = literal.fields.collect({ case v @ Variable(_, _) => v }).sorted.distinct
    val ansInstance = shuffledSupport.foldLeft(Instance(ansSignature.map(_.domain)))(_ + _)
    AssignmentTrie(ansSignature, ansInstance)
  }

  def join[T <: Value[T]](at1: AssignmentTrie[T], at2: AssignmentTrie[T])
                         (implicit ordering: Ordering[Variable], vs: Semiring[T]): AssignmentTrie[T] = Timers("AssignmentTrie.join") {

    def _join(sign1: IndexedSeq[Variable], inst1: Instance[T],
              sign2: IndexedSeq[Variable], inst2: Instance[T]): Instance[T] = {

      if (sign1.nonEmpty && sign2.nonEmpty) {

        val (head1, head2) = (sign1.head, sign2.head)
        if (ordering.lt(head1, head2)) {
          val InstanceInd(domHead, _, map1) = inst1
          val domTailAns = (sign1.tail ++ sign2).distinct.sorted.map(_.domain)
          val mapAns = for ((c1, instTl1) <- map1) yield c1 -> _join(sign1.tail, instTl1, sign2, inst2)
          InstanceInd(domHead, domTailAns, mapAns)
        } else if (ordering.equiv(head1, head2)) {
          val InstanceInd(domHead, domTail1, map1) = inst1
          val InstanceInd(_, domTail2, map2) = inst2
          val domTailAns = (sign1.tail ++ sign2.tail).distinct.sorted.map(_.domain)
          val mapAns = (for (c <- map1.keySet ++ map2.keySet;
                             instTl1 = map1.getOrElse(c, Instance(domTail1));
                             instTl2 = map2.getOrElse(c, Instance(domTail2));
                             instTl = _join(sign1.tail, instTl1, sign2.tail, instTl2))
                        yield c -> instTl).toMap
          InstanceInd(domHead, domTailAns, mapAns)
        } else {
          Contract.assert(ordering.gt(head1, head2))
          val InstanceInd(domHead, _, map2) = inst2
          val domTailAns = (sign1 ++ sign2.tail).distinct.sorted.map(_.domain)
          val mapAns = for ((c2, instTl2) <- map2) yield c2 -> _join(sign1, inst1, sign2.tail, instTl2)
          InstanceInd(domHead, domTailAns, mapAns)
        }

      } else if (sign1.isEmpty) {
        val InstanceBase(v1) = inst1
        inst2 * v1
      } else {
        Contract.assert(sign2.isEmpty)
        val InstanceBase(v2) = inst2
        inst1 * v2
      }

    }

    val signature = (at1.signature ++ at2.signature).sorted.distinct
    val instance = _join(at1.signature, at1.instance, at2.signature, at2.instance)
    AssignmentTrie(signature, instance)

  }

  def project[T <: Value[T]](at: AssignmentTrie[T], varSet: Set[Variable])
                            (implicit ordering: Ordering[Variable], vs: Semiring[T]): AssignmentTrie[T] = {

    def pi(instance: Instance[T], bv: IndexedSeq[Boolean], varVec: IndexedSeq[Variable]): Instance[T] = instance match {
      case InstanceBase(_) => instance

      case InstanceInd(domHead, _, map) if bv.head =>
        val domTailAns = varVec.tail.map(_.domain)
        val mmap = for ((c, inst) <- map) yield c -> pi(inst, bv.tail, varVec.tail)
        InstanceInd(domHead, domTailAns, mmap)

      case InstanceInd(_, _, map) if !bv.head =>
        val domAns = varVec.map(_.domain)
        map.values.foldLeft(Instance(domAns))((sum, inst) => sum ++ pi(inst, bv.tail, varVec))
    }

    val varVec = varSet.toVector.sorted
    AssignmentTrie(varVec, pi(at.instance, at.signature.map(varSet), varVec))

  }

}
