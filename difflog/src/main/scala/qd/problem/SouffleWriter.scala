package qd
package problem

import java.io.{File, PrintWriter}

import qd.util.Contract

object SouffleWriter {

  val numDomain = Domain("number")
  val ruleRel = Relation("Rule", Vector(numDomain))

  def write(query: Problem, outputDirectoryName: String): Unit = {
    val outputDirectory = new File(outputDirectoryName)
    if (!outputDirectory.exists()) {
      outputDirectory.mkdir()
    }
    require(outputDirectory.isDirectory)

    writeRules(query, outputDirectoryName)
    writeInputRels(query, outputDirectoryName)
    writeOutputRels(query, outputDirectoryName)
  }

  def indexedRule(rule: Rule, index: Int): Rule = {
    val indexLiteral = ruleRel(Vector(Constant(index, numDomain)))
    Rule(rule.lineage, rule.head, rule.body :+ indexLiteral)
  }

  def eInstrument(rule: Rule, index: Int, eRelMap: Map[Relation, Relation]): Set[Rule] = {
    // Let rule be of the form Rh(vh) :- R1(v1), R2(v2), ..., Rk(vk). Then, ...

    // rDirect is the rule of the form Rh_E(vh, rule) :- R1(v1), R2(v2), ..., Rk(vk), Rule(rule).
    val rConst = Constant(index, numDomain)
    val rDirectHead = eRelMap(rule.head.relation)(rule.head.fields :+ rConst)
    val rDirectBody = rule.body :+ ruleRel(Vector(rConst))
    val rDirect: Rule = Rule(rule.lineage, rDirectHead, rDirectBody)

    // For each literal Ri(vi) in rule, rTransfer contains a rule of the form
    // Rh_E(vh, ruleIndex) :- R1(v1), R2(v2), ..., R{i - 1}(v{i - 1}), Ri_E(vi, ruleIndex), R{i + 1}(v{i + 1}), ..., Rk(vk), Rule(rule).
    val rTransfer = for ((lit, index) <- rule.body.zipWithIndex;
                         rPre = rule.body.take(index);
                         rPost = rule.body.drop(index + 1))
                    yield {
                      val rVar = Variable("ruleIndex", numDomain)
                      val head: Literal = eRelMap(rule.head.relation)(rule.head.fields :+ rVar)
                      val liti = eRelMap(lit.relation)(lit.fields :+ rVar)
                      val body = (rPre :+ liti) ++ rPost :+ ruleRel(Vector(rConst))
                      Rule(rule.lineage, head, body)
                    }

    rTransfer.toSet + rDirect
  }

  // Returns a string instead of a rule because the instrumented rule contains a special literal "r != index", which
  // we cannot represent in Difflog.
  // A new variable "ruleIndex" is introduced for instrumentation. We hope that the name of this variable does not clash
  // with any variable already being used in the rule.
  def enInstrument(rule: Rule, index: Int, enRelMap: Map[Relation, Relation]): String = {
    val rVar = Variable("ruleIndex", numDomain)
    val newHead = enRelMap(rule.head.relation)(rule.head.fields :+ rVar)

    val indexLiteral = ruleRel(Vector(Constant(index, numDomain)))
    val newBody = rule.body.map(literal => enRelMap(literal.relation)(literal.fields :+ rVar)).map(_.toString) :+
                  s"$rVar != $index" :+
                  indexLiteral.toString

    s"$newHead :- ${newBody.mkString(", ")}."
  }

  def writeRules(query: Problem, outputDirectoryName: String): Unit = {
    val rulesFile = new PrintWriter(outputDirectoryName + "/rules.dl")
    val ruleNamesFile = new PrintWriter(outputDirectoryName + "/ruleNames.txt")
    val eInstrumentedRulesFile = new PrintWriter(outputDirectoryName + "/rules-einstr.dl")
    val enInstrumentedRulesFile = new PrintWriter(outputDirectoryName + "/rules-eninstr.dl")
    val instrumentedRulesFile = new PrintWriter(outputDirectoryName + "/rules-instr.dl")

    try {

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // 1. Declare all domains

      val allDomains = (query.inputRels ++ query.inventedRels ++ query.outputRels).flatMap(_.signature)
      Contract.deepRequire(!allDomains.exists(_.name == "number"))
      for (pw <- Seq(rulesFile, eInstrumentedRulesFile, enInstrumentedRulesFile, instrumentedRulesFile)) {
        for (domain <- allDomains) {
          pw.println(s".type $domain")
        }
        pw.println("")
      }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // 2. Declare all relations

      def declRelation(rel: Relation, mode: String, pw: PrintWriter): Unit = {
        Contract.deepRequire(mode == "input" || mode == "output")
        val indexedSignature = rel.signature.zipWithIndex.map({ case (domain, index) => s"v$index: $domain" })
        pw.println(s".decl ${rel.name}(${indexedSignature.mkString(", ")})")
        pw.println(s".$mode ${rel.name}")
      }

      ////
      // 2a. Declare rule names

      for (pw <- Seq(rulesFile, eInstrumentedRulesFile, enInstrumentedRulesFile, instrumentedRulesFile)) {
        declRelation(ruleRel, "input", pw)
        pw.println("")
      }

      ////
      // 2b. Declare uninstrumented relations

      for (pw <- Seq(rulesFile, eInstrumentedRulesFile, enInstrumentedRulesFile, instrumentedRulesFile)) {
        for (rel <- query.inputRels) declRelation(rel, "input", pw)
        pw.println("")

        for (rels <- Seq(query.inventedRels, query.outputRels)) {
          for (rel <- rels) declRelation(rel, "output", pw)
          pw.println("")
        }
      }

      ////
      // 2b. Declare instrumented relations

      // 2b(i). E-provenance (or all-provenance)

      val eRelMap = (query.inputRels ++ query.inventedRels ++ query.outputRels).map({ rel =>
        val eName = s"${rel.name}_E"
        Contract.deepRequire(!query.inventedRels.exists(_.name == eName))
        Contract.deepRequire(!query.outputRels.exists(_.name == eName))
        rel -> Relation(eName, rel.signature :+ numDomain)
      }).toMap

      for (pw <- Seq(eInstrumentedRulesFile, instrumentedRulesFile)) {
        for (rels <- Seq(query.inputRels, query.inventedRels, query.outputRels)) {
          for (rel <- rels) declRelation(eRelMap(rel), "output", pw)
          pw.println("")
        }
      }

      // 2b(ii). EN-provenance (NEN-provenance = A-provenance, or co-provenance)

      val enRelMap = (query.inputRels ++ query.inventedRels ++ query.outputRels).map({ rel =>
        val enName = s"${rel.name}_EN"
        Contract.deepRequire(!query.inventedRels.exists(_.name == enName))
        Contract.deepRequire(!query.outputRels.exists(_.name == enName))
        rel -> Relation(enName, rel.signature :+ Domain("number"))
      }).toMap

      for (pw <- Seq(enInstrumentedRulesFile, instrumentedRulesFile)) {
        for (rels <- Seq(query.inputRels, query.inventedRels, query.outputRels)) {
          for (rel <- rels) declRelation(enRelMap(rel), "output", pw)
          pw.println("")
        }
      }

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // 3. Print all rules

      def printRule(rule: Rule, pw: PrintWriter): Unit = {
        pw.println(s"${rule.head} :- ${rule.body.mkString(", ")}.")
      }

      ////
      // 3a. EN base instrumentations
      //     inputRel_EN(t, ruleIndex) :- inputRel(t), Rule(ruleIndex).

      for (pw <- Seq(enInstrumentedRulesFile, instrumentedRulesFile)) {
        for (rel <- query.inputRels) {
          val rVar = Variable("ruleIndex", numDomain)
          val tVarVec = rel.signature.zipWithIndex.map({ case (dom, index) => Variable(s"v$index", dom) })
          val head = enRelMap(rel)(tVarVec :+ rVar)
          val body = Vector(rel(tVarVec), ruleRel(Vector(rVar)))
          val rule = Rule(Empty, head, body)

          printRule(rule, pw)
        }
      }

      query.rules.zipWithIndex.foreach { case (rule, index) =>

        ////
        // 3b. Print rule name

        ruleNamesFile.println(index)

        ////
        // 3c. Print uninstrumented rule

        for (pw <- Seq(rulesFile, eInstrumentedRulesFile, enInstrumentedRulesFile, instrumentedRulesFile)) {
          printRule(indexedRule(rule, index), pw)
        }

        ////
        // 3d. Print E-instrumented rules

        for (pw <- Seq(eInstrumentedRulesFile, instrumentedRulesFile)) {
          for (rulePrime <- eInstrument(rule, index, eRelMap)) {
            printRule(rulePrime, pw)
          }
        }

        ////
        // 3e. Print EN-instrumented rule

        for (pw <- Seq(enInstrumentedRulesFile, instrumentedRulesFile)) {
          pw.println(enInstrument(rule, index, enRelMap))
        }

      }

    } finally {
      rulesFile.close()
      ruleNamesFile.close()
      eInstrumentedRulesFile.close()
      enInstrumentedRulesFile.close()
      instrumentedRulesFile.close()
    }
  }

  def writeInputRels(query: Problem, outputDirectoryName: String): Unit = {
    for (rel <- query.inputRels) {
      val relFile = new PrintWriter(outputDirectoryName + s"/${rel.name}.facts")
      try {
        query.discreteEDB(rel).foreach { t =>
          relFile.println(t.fields.mkString("\t"))
        }
      } finally {
        relFile.close()
      }
    }
  }

  def writeOutputRels(query: Problem, outputDirectoryName: String): Unit = {
    for (rel <- query.outputRels) {
      val relFile = new PrintWriter(outputDirectoryName + s"/${rel.name}.expected")
      try {
        query.discreteIDB(rel).foreach { t =>
          relFile.println(t.fields.mkString("\t"))
        }
      } finally {
        relFile.close()
      }
    }
  }

}
