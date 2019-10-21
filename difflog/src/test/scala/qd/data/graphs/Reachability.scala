package qd
package data
package graphs

object Reachability {

  val te = Token("E")
  val tt = Token("T")

  val node: Domain = Graphs.node
  val edge: Relation = Graphs.edge
  val path: Relation = Graphs.path

  val x = Variable("x", node)
  val y = Variable("y", node)
  val z = Variable("z", node)

  val ruleE = Rule(te, path(Vector(x, y)), Vector(edge(Vector(x, y))))
  val rulePE = Rule(tt, path(Vector(x, z)), Vector(path(Vector(x, y)), edge(Vector(y, z))))
  val ruleEP = Rule(tt, path(Vector(x, z)), Vector(edge(Vector(x, y)), path(Vector(y, z))))
  val rulePP = Rule(tt, path(Vector(x, z)), Vector(path(Vector(x, y)), path(Vector(y, z))))

  val PE: (String, Set[Rule]) = ("PE", Set(ruleE, rulePE))
  val EP: (String, Set[Rule]) = ("EP", Set(ruleE, ruleEP))
  val PP: (String, Set[Rule]) = ("PP", Set(ruleE, rulePP))

  val Programs: Set[(String, Set[Rule])] = Set(PE, EP, PP)

}
