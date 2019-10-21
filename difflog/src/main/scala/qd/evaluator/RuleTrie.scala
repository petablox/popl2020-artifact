package qd.evaluator

import qd.util.Contract
import qd.{Literal, Rule, Variable}

import scala.collection.immutable.Iterable

class RuleTrie private (val leaves: Set[Rule], val map: Map[Literal, RuleTrie]) extends Iterable[Rule] {

  Contract.deepRequire(map.forall { case (literal, trie) => trie.forall(_.body.contains(literal)) })

  // Savings = totalLiterals (of soup from which this trie is constructed) / numLiterals (which remain after collapse)
  val numRules: Int = leaves.size + map.values.map(_.numRules).sum
  val numLiterals: Int = map.map({ case (_, subTrie) => 1 + subTrie.numLiterals }).sum
  val totalLiterals: Int = map.values.map(subTrie => subTrie.totalLiterals + subTrie.numRules).sum

  override def iterator: Iterator[Rule] = map.values.foldLeft(leaves.iterator)(_ ++ _.iterator)
  val variables: Set[Variable] = {
    val vs1 = leaves.flatMap(_.head.variables)
    val vs2 = map.flatMap { case (l, t) => l.variables ++ t.variables }
    vs1 ++ vs2
  }

  def +(rule: Rule): RuleTrie = {
    def add(remainingLiterals: Seq[Literal], trie: RuleTrie): RuleTrie = {
      if (remainingLiterals.isEmpty) new RuleTrie(trie.leaves + rule, trie.map)
      else {
        val litHead = remainingLiterals.head
        val litRest = remainingLiterals.tail
        val subTrie = trie.map.getOrElse(litHead, RuleTrie())
        new RuleTrie(trie.leaves, trie.map + (litHead -> add(litRest, subTrie)))
      }
    }
    add(rule.body.sortBy(_.toString), this)
  }

}

object RuleTrie {
  def apply(): RuleTrie = new RuleTrie(Set(), Map())
  def apply(rules: Iterable[Rule]): RuleTrie = rules.foldLeft(RuleTrie())(_ + _)
}
