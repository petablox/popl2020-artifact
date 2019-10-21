package scalaz3

import sbt._
import Keys._
import org.eclipse.jgit.api._

import scala.sys.process.Process

object ScalaZ3Plugin extends AutoPlugin {
  override lazy val projectSettings = Seq(commands += scalaZ3Command)

  lazy val scalaZ3Repo = "git://github.com/epfl-lara/ScalaZ3.git"

  lazy val scalaZ3Command = 
    Command.command("scalaZ3") { (state: State) => 
      cloneScalaZ3(state.log)
      buildScalaZ3(state.log)
      copyScalaZ3Jar(state, state.log)
      state
    }

  lazy val scalaZ3Path = file(".") / "ScalaZ3" 

  def cloneScalaZ3(log : Logger) : Unit = {
    if (!scalaZ3Path.asFile.exists) {
      Git.cloneRepository()
        .setDirectory(scalaZ3Path.asFile)
        .setURI(scalaZ3Repo)
        .call()
      log.info("Cloned ScalaZ3...")
    } else {
      log.info("Found ScalaZ3...")
    }
  }

  def exec(cmd: String, dir: File, log : Logger) : Int = {
    log.info("$ cd " + dir + " && "+cmd)
    Process(cmd, dir) ! log
  }

  def buildScalaZ3(log : Logger) : Unit = {
    log.info("Building ScalaZ3...")
    exec("sbt package", scalaZ3Path, log)
    log.info("Built ScalaZ3...")
  }

  def copyScalaZ3Jar(state: State, log : Logger) : Unit = {
    val srcPath = scalaZ3Path / "target" / "scala-2.12" / "scalaz3_2.12-3.0.jar"
    val libDir = file(".") / "lib" 

    exec("mkdir -p " + libDir, file("."), log)

    val destPath = file(".") / "lib" / "scalaz3_2.12-3.0.jar"
    log.info("Copying ScalaZ3 jar from " + srcPath + " to " + destPath)
    exec("cp " + srcPath + " " + destPath + "", file("."), log)
  }
}
