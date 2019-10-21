package qd.util

import scala.collection.mutable

object Counters {

  private val counters: mutable.Map[Any, Long] = mutable.Map()

  def apply[T](name: Any)(thunk: => T): T = {
    counters.synchronized {
      if (!counters.contains(name)) counters.put(name, 0l)
      val count = counters(name)
      counters += name -> (count + 1)
    }
    thunk
  }

  def getSnapshot: Map[Any, Long] = counters.toMap
  def reset(): Unit = counters.synchronized { counters.clear() }

}
