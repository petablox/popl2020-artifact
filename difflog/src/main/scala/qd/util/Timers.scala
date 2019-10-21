package qd
package util

import scala.collection.mutable

object Timers {

  case class Timer(duration: Long, invocations: Long)
  private val timers: mutable.Map[Any, Timer] = mutable.Map()

  def apply[T](name: Any)(thunk: => T): T = {
    val startTime = System.nanoTime()
    val ans: T = thunk
    val endTime = System.nanoTime()
    timers.synchronized {
      if (!timers.contains(name)) timers.put(name, Timer(0l, 0))
      val Timer(duration, invocations) = timers(name)
      val newDuration = duration + (endTime - startTime)
      val newInvocations = invocations + 1
      timers += name -> Timer(newDuration, newInvocations)
    }
    ans
  }

  def getSnapshot: Map[Any, Timer] = timers.toMap
  def reset(): Unit = timers.synchronized { timers.clear() }

}
