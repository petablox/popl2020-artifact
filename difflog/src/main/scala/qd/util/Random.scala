package qd
package util

import org.apache.commons.math3.random.MersenneTwister

object Random {
  private val random = new MersenneTwister()
  def nextDouble(): Double = nextDouble(0.0, 1.0)
  def nextDouble(lo: Double, hi: Double): Double = {
    Contract.require(lo <= hi)
    val preAns = this.synchronized { random.nextDouble() }
    val ans = lo + preAns * (hi - lo)
    Contract.assert(lo <= ans && ans <= hi)
    ans
  }
  def nextInt(lo: Int, hi: Int): Int = {
    Contract.require(lo <= hi)
    this.synchronized { random.nextInt(hi - lo) + lo }
  }
  def pick[T](set: Set[T]): T = {
    val vector = set.toVector
    vector(nextInt(0, vector.size))
  }
}
