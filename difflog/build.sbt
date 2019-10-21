import Dependencies._

sbtPlugin := true

lazy val root = (project in file("."))
  .enablePlugins(ScalaZ3Plugin)
  .settings(
    inThisBuild(List(
      organization := "edu.upenn.cis",
      scalaVersion := "2.12.3",
      version      := "0.1.0-SNAPSHOT"
    )),
    name := "QD",

    libraryDependencies += "org.apache.commons" % "commons-math3" % "3.6.1",
    libraryDependencies += "org.scala-lang.modules" %% "scala-parser-combinators" % "1.1.1",
    libraryDependencies += "com.outr" %% "scribe" % "2.6.0",

    libraryDependencies += scalaTest % Test,
    libraryDependencies += "org.scalacheck" %% "scalacheck" % "1.14.0" % "test",
    testOptions in Test += Tests.Argument(TestFrameworks.ScalaTest, "-oD"),

    // https://tpolecat.github.io/2017/04/25/scalac-flags.html
    scalacOptions ++= Seq(
      "-deprecation",                      // Emit warning and location for usages of deprecated APIs.
      "-explaintypes",                     // Explain type errors in more detail.
      "-feature",                          // Emit warning and location for usages of features that should be imported explicitly.
      "-unchecked",                        // Enable additional warnings where generated code depends on assumptions.
      "-Xcheckinit",                       // Wrap field accessors to throw an exception on uninitialized access.
      // "-Xfatal-warnings",                  // Fail the compilation if there are any warnings.
      "-Xlint:_",
      "-Ywarn-dead-code",                  // Warn when dead code is identified.
      "-Ywarn-extra-implicit",             // Warn when more than one implicit parameter section is defined.
      "-Ywarn-inaccessible",               // Warn about inaccessible types in method signatures.
      "-Ywarn-infer-any",                  // Warn when a type argument is inferred to be `Any`.
      "-Ywarn-nullary-override",           // Warn when non-nullary `def f()' overrides nullary `def f'.
      "-Ywarn-nullary-unit",               // Warn when nullary methods return Unit.
      "-Ywarn-numeric-widen",              // Warn when numerics are widened.
      "-Ywarn-unused:_",
      "-Ywarn-value-discard"               // Warn when non-Unit expression results are unused.
    )
  )
