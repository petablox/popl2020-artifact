package qd

import qd.util.Contract

object RuleEnumerator {

  def enumerate(
                 inputRels: Set[Relation], inventedRels: Set[Relation], outputRels: Set[Relation],
                 maxLiterals: Int, maxVars: Int
               ): Set[Rule] = {

    Contract.require(inputRels.intersect(inventedRels).isEmpty)
    Contract.require(inputRels.intersect(outputRels).isEmpty)
    Contract.require(inventedRels.intersect(outputRels).isEmpty)
    Contract.require(maxLiterals >= 0 && maxVars >= 0)

    val allRels = inputRels ++ inventedRels ++ outputRels

    def allLiteralSets(length: Int, freeVars: Set[Variable]): Set[Set[Literal]] = {
      Contract.require(length >= 0)
      if (length == 0) Set(Set())
      else {
        def allLiterals(hypRel: Relation): Set[(Literal, Set[Variable])] = {
          def allBindings(signature: IndexedSeq[Domain], fvp: Set[Variable]): Set[Vector[Variable]] = {
            if (signature.isEmpty) Set(Vector())
            else {
              val domHead = signature.head
              def newVar(): Variable = {
                var index = 0
                while (fvp.contains(Variable(s"v$index", domHead))) index = index + 1
                Variable(s"v$index", domHead)
              }
              var availableVars = if (fvp.size < maxVars) fvp + newVar() else fvp
              availableVars = availableVars.filter(_.domain == domHead)
              for (bhead <- availableVars; brest <- allBindings(signature.tail, fvp + bhead))
              yield bhead +: brest
            }
          }
          for (binding <- allBindings(hypRel.signature, freeVars))
          yield (Literal(hypRel, binding), freeVars ++ binding)
        }
        for (hypRel <- allRels;
             (lit, fvp) <- allLiterals(hypRel);
             lits <- allLiteralSets(length - 1, fvp))
        yield lits + lit
      }
    }

    val allBodies = (0 to maxLiterals).flatMap(length => allLiteralSets(length, Set()))
                                      .toSet

    def allHeads(targetRel: Relation, body: Set[Literal]): Set[Literal] = {
      val allVars = body.flatMap(_.variables)
      def allBindings(signature: IndexedSeq[Domain]): Set[Vector[Variable]] = {
        if (signature.isEmpty) Set(Vector())
        else {
          val availableVars = allVars.filter(_.domain == signature.head)
          for (bhead <- availableVars; brest <- allBindings(signature.tail))
          yield bhead +: brest
        }
      }
      for (binding <- allBindings(targetRel.signature))
      yield Literal(targetRel, binding)
    }

    def reachableVars(rule: Rule): Set[Variable] = {
      var (ans, candidate) = (Set[Variable](), rule.head.variables)
      val rbs = rule.body.toSet
      while (ans != candidate) {
        ans = candidate
        candidate = for (lit <- rbs if lit.variables.intersect(ans).nonEmpty; v <- lit.variables)
                    yield v
      }
      ans
    }

    def isDegenerate(rule: Rule): Boolean = {
      rule.body.contains(rule.head) || reachableVars(rule).size < rule.variables.size
    }

    val unnamedRules = for (targetRel <- inventedRels ++ outputRels;
                            body <- allBodies;
                            head <- allHeads(targetRel, body);
                            rule = Rule(Token(s"R"), head, body.toVector)
                            if !isDegenerate(rule))
                       yield {
                         rule.normalized
                       }

    var ruleIndex = 0
    for (rule <- unnamedRules)
    yield {
      ruleIndex = ruleIndex + 1
      Rule(Token(s"R$ruleIndex"), rule.head, rule.body)
    }

  }

}
