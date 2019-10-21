package qd
package tokenvec

import qd.instance.Config
import qd.util.Contract

case class Line(points: IndexedSeq[TokenVec]) extends (Token => VecValue[FValue]) {

  Contract.require(points.nonEmpty)
  val tokens: Set[Token] = points.head.keySet
  Contract.require(points.map(_.keySet).forall(_ == tokens))

  override def apply(token: Token): VecValue[FValue] = VecValue(points.map(_(token)))

}

object Line {

  def invert(cvf: Config[VecValue[FValue]]): Vector[Config[FValue]] = {
    var ans: Option[Vector[Config[FValue]]] = None
    for ((rel, vecInstance) <- cvf.map) {
      for ((t, vs) <- vecInstance.support) {
        if (ans.isEmpty) ans = Some(Vector.fill(vs.vec.length)(Config()))
        else Contract.require(vs.vec.length == ans.get.length)

        val agv = ans.get.zip(vs.vec)
        ans = Some(agv.map { case (cfg, v) => cfg.add(rel, t, v) })
      }
    }
    ans.get
  }

}
