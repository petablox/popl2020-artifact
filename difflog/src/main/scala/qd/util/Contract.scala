package qd.util

object Contract {
  // By factoring out calls to Predef.require(...) and Predef.assert(...), we can turn them off and on to determine
  // performance penalties

  val CHECK_CONTRACTS: Boolean = true
  val DEEP_CHECK_CONTRACTS: Boolean = false
  val VERBOSE: Boolean = sys.env.getOrElse("VERBOSE", "0") != "0"

  def require(predicate: => Boolean): Unit = if (CHECK_CONTRACTS) Predef.require(predicate)
  def require(predicate: => Boolean, message: => Any): Unit = if (CHECK_CONTRACTS) Predef.require(predicate, message)

  def requireIf(guard: => Boolean, predicate: => Boolean): Unit = require(!guard || predicate)
  def requireIf(guard: => Boolean, predicate: => Boolean, message: => Any): Unit = require(!guard || predicate, message)

  def deepRequire(predicate: => Boolean): Unit = if (DEEP_CHECK_CONTRACTS) Predef.require(predicate )
  def deepRequire(predicate: => Boolean, message: => Any): Unit = if (DEEP_CHECK_CONTRACTS)
                                                                    Predef.require(predicate, message)

  def assert(predicate: => Boolean): Unit = if (CHECK_CONTRACTS) Predef.assert(predicate)
  def assert(predicate: => Boolean, message: => Any): Unit = if (CHECK_CONTRACTS) Predef.assert(predicate, message)

  def deepAssert(predicate: => Boolean): Unit = if (DEEP_CHECK_CONTRACTS) Predef.assert(predicate)
  def deepAssert(predicate: => Boolean, message: => Any): Unit = if (DEEP_CHECK_CONTRACTS)
                                                                   Predef.assert(predicate, message)
}
