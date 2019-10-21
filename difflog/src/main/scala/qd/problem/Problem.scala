package qd
package problem

import qd.Semiring.FValueSemiringObj
import qd.instance.{Config, Instance}
import qd.tokenvec.TokenVec
import qd.util.Random
import util.Contract

class Problem private (
                        val inputRels: Set[Relation],
                        val inventedRels: Set[Relation],
                        val outputRels: Set[Relation],

                        val discreteEDB: Map[Relation, Set[DTuple]],
                        val discreteIDB: Map[Relation, Set[DTuple]],

                        val pos: TokenVec,
                        val rules: Set[Rule],

                        val dom2values : Map[Domain, Set[Constant]] = Map.empty[Domain,Set[Constant]],
                        val allOutTuples : Map[Relation, Set[DTuple]] = Map.empty[Relation, Set[DTuple]]
                      ) {


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // 1. Relations

  ////
  // 1a. Accessors

  def findRel(pred: Relation => Boolean): Option[Relation] = {
    val f1 = inputRels.find(pred)
    val f2 = inventedRels.find(pred)
    val f3 = outputRels.find(pred)
    f1 orElse f2 orElse f3
  }
  def knownRelation(rel: Relation): Boolean = findRel(_ == rel).nonEmpty
  def isNewRelation(rel: Relation): Boolean = !knownRelation(rel)

  ////
  // 1b. Modifiers

  private def addRel(rels: Set[Relation], newRel: Relation): Set[Relation] = {
    Contract.require(isNewRelation(newRel), s"Relation $newRel multiply declared")
    rels + newRel
  }

  def addInputRel(rel: Relation): Problem = {
    new Problem(addRel(inputRels, rel), inventedRels, outputRels, discreteEDB + (rel -> Set()), discreteIDB, pos, rules, dom2values, allOutTuples)
  }

  def addInventedRel(rel: Relation): Problem = {
    new Problem(inputRels, addRel(inventedRels, rel), outputRels, discreteEDB, discreteIDB, pos, rules, dom2values, allOutTuples)
  }

  def addOutputRel(rel: Relation): Problem = {
    new Problem(inputRels, inventedRels, addRel(outputRels, rel), discreteEDB, discreteIDB + (rel -> Set()), pos, rules, dom2values, allOutTuples)
  }


  def addDom2values(d2v :  Map[Domain, Set[Constant]]) : Problem = {
    new Problem(inputRels, inventedRels, outputRels, discreteEDB, discreteIDB, pos, rules, d2v, allOutTuples)
  }

  def genTuples(sig:IndexedSeq[Domain], k:Int): Set[ Vector[Constant] ] = {
    if (k <= 0) Set( Vector.empty )
    else {
      for {v <- dom2values(sig(k-1)); partial <- genTuples(sig, k-1) } yield partial :+ v
    }
  }

  def addOutputRelThenDump(rel: Relation): Problem = {
    val relTuples = genTuples(rel.signature, rel.signature.size).map(x => DTuple(x))

    new Problem(inputRels, inventedRels, addRel(outputRels, rel), discreteEDB, discreteIDB + (rel -> Set()), pos, rules,
      dom2values, allOutTuples + (rel -> relTuples))
  }

  // inject noise
  def injectNoise() : Problem = {
    // randomly pick an output relation and an output tuple
    val rel = Random.pick(outputRels)
    val noiseTuple = Random.pick( allOutTuples(rel) )
    val cleanIDB = discreteIDB(rel)
    val noisyIDB = if (cleanIDB.contains(noiseTuple)) { cleanIDB - noiseTuple } else { cleanIDB + noiseTuple }

    new Problem(inputRels, inventedRels, outputRels, discreteEDB,  discreteIDB + (rel -> noisyIDB), pos, rules, dom2values, allOutTuples)
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // 2. EDB and IDB

  ////
  // 2a. Discrete EDB to Configuration

  def discreteTuplesToInstance(relation: Relation, tuples: Set[DTuple]): Instance[FValue] = {
    tuples.foldLeft(Instance(relation.signature)) { case (instance, t) =>
      instance + (t -> FValueSemiringObj.One)
    }
  }

  lazy val edb: Config[FValue] = Config(discreteEDB.map { case (rel, ts) => rel -> discreteTuplesToInstance(rel, ts) })
  lazy val idb: Config[FValue] = Config(discreteIDB.map { case (rel, ts) => rel -> discreteTuplesToInstance(rel, ts) })

  ////
  // 2b. Adding tuples

  private def addTuples(
                         config: Map[Relation, Set[DTuple]],
                         rts: collection.immutable.Seq[(Relation, DTuple)]
                       ): Map[Relation, Set[DTuple]] = {
    rts.foldLeft(config) { case (cfg, (rel, tuple)) =>
      Contract.require(config.contains(rel), s"Undeclared relation $rel")
      cfg + (rel -> (cfg(rel) + tuple))
    }
  }

  def addEDBTuples(rts: collection.immutable.Seq[(Relation, DTuple)]): Problem = {
    new Problem(inputRels, inventedRels, outputRels, addTuples(discreteEDB, rts), discreteIDB, pos, rules, dom2values, allOutTuples)
  }

  def addIDBTuples(rts: collection.immutable.Seq[(Relation, DTuple)]): Problem = {
    new Problem(inputRels, inventedRels, outputRels, discreteEDB, addTuples(discreteIDB, rts), pos, rules, dom2values, allOutTuples)
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // 3. Tokens and Rules

  def allTokens: Set[Token] = pos.keySet

  def addToken(token: Token, value: Double): Problem = {
    if (pos.contains(token)) {
      scribe.info(s"Ignoring redeclaration of token $token. Already initialized to ${pos(token)}")
      return this
    }
    new Problem(inputRels, inventedRels, outputRels, discreteEDB, discreteIDB, pos + (token -> value), rules, dom2values, allOutTuples)
  }

  def addRule(rule: Rule): Problem = {
    Contract.require(knownRelation(rule.head.relation))
    Contract.require(rule.body.forall(literal => knownRelation(literal.relation)))
    Contract.require(rule.lineage.tokenSet.forall(token => pos.contains(token)))
    new Problem(inputRels, inventedRels, outputRels, discreteEDB, discreteIDB, pos, rules + rule, dom2values, allOutTuples)
  }

  def addRules(newRules: Set[Rule]): Problem = newRules.foldLeft(this)(_ addRule _)

}

object Problem {
  val Empty: Problem = new Problem(Set(), Set(), Set(), Map(), Map(), TokenVec(Map()), Set())
}
