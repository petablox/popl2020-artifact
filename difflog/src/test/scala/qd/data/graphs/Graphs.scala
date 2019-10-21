package qd
package data
package graphs

import qd.instance.{Config, Instance}

import scala.util.Random

object Graphs {

  val node: Domain = Domain("Node")
  val edge: Relation = Relation("edge", Vector(node, node))
  val path = Relation("path", Vector(node, node))
  val scc = Relation("scc", Vector(node, node))

  val Graphs: Set[Graph] = Set(smallGraph) ++
                           Range(1, 16, 2).map(line).toSet ++
                           Range(1, 16, 2).map(circle).toSet +
                           erdosRenyi(50, 0.1, 0) + erdosRenyi(100, 0.01, 0)

  case class Graph(name: Any, nodeSet: Set[Constant], edgeSet: Set[(Constant, Constant)]) {
    require(nodeSet.nonEmpty)
    require(nodeSet.forall(_.domain == node))
    require(edgeSet.forall { case (from, to) => nodeSet(from) && nodeSet(to) })

    lazy val edb: Config[FValue] = {
      val vs: Semiring[FValue] = implicitly[Semiring[FValue]]
      val edgeTuples = edgeSet.map { case (a, b) => DTuple(Vector(a, b)) -> vs.One }
      val edgeInstance = edgeTuples.foldLeft(Instance[FValue](Vector(node, node)))(_ + _)
      Config(Map(edge -> edgeInstance))
    }

    lazy val reachable: Set[(Constant, Constant)] = {
      def int(steps: Int): Set[(Constant, Constant)] = {
        require(steps >= 1)
        if (steps == 1) edgeSet
        else {
          val rn1 = int(steps - 1)
          val r = for ((i, j) <- rn1; (k, l) <- edgeSet; if j == k) yield (i, l)
          rn1 ++ r
        }
      }
      int(nodeSet.size + 1)
    }

    lazy val components: Set[(Constant, Constant)] = reachable.filter(p => reachable((p._2, p._1)))
  }

  def vertex(name: Any): Constant = Constant(name, node)

  def smallGraph: Graph = {
    val node1 = vertex(1)
    val node2 = vertex(2)
    val node3 = vertex(3)
    val nodeSet = Set(node1, node2, node3)
    val edgeSet = Set((node1, node2), (node2, node2), (node2, node3))
    Graph("SmallGraph", nodeSet, edgeSet)
  }

  def line(n: Int): Graph = {
    require(n > 0)
    val nodeSet = Range(0, n).map(i => vertex(i)).toSet
    val edgeSet = Range(0, n - 1).map(i => (vertex(i), vertex(i + 1))).toSet
    Graph(s"Line($n)", nodeSet, edgeSet)
  }

  def circle(n: Int): Graph = {
    require(n > 0)
    val nodeSet = Range(0, n).map(i => vertex(i)).toSet
    val edgeSet = Range(0, n).map(i => (vertex(i), vertex((i + 1) % n))).toSet
    Graph(s"Circle($n)", nodeSet, edgeSet)
  }

  def lasso(m: Int, n: Int): Graph = {
    require(m > 0 && n > 0)
    val aNodes = Range(0, m).map(i => vertex(s"a$i")).toSet
    val bNodes = Range(0, n).map(i => vertex(s"b$i")).toSet
    val edgeSet = Range(0, m - 1).map(i => (vertex(s"a$i"), vertex(s"a${i + 1}"))).toSet ++
                  Set((vertex(s"a${m - 1}"), vertex(s"b${0}"))) ++
                  Range(0, n).map(i => (vertex(s"b$i"), vertex(s"b${(i + 1) % n}"))).toSet
    Graph(s"Lasso($m, $n)", aNodes ++ bNodes, edgeSet)
  }

  def erdosRenyi(n: Int, p: Double, seed: Int): Graph = {
    require(n > 0 && 0.0 <= p && p <= 1.0)
    val random = new Random(seed)
    val nodeSet = Range(0, n).map(i => vertex(i)).toSet
    val edgeSet = for (i <- nodeSet; j <- nodeSet; if random.nextDouble() < p) yield (i, j)
    Graph(s"Erdos-Renyi($n, $p, $seed)", nodeSet, edgeSet)
  }

}
