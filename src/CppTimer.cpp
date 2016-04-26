/*
 * CppTimer.cpp
 *
 *  Created on: 27-Apr-2016
 *      Author: ankithbti
 */

#include <cppTimer/CppTimer.hpp>

namespace cppTimer
{

  CppTimer::CppTimer(CppTimerI::Task task, long millisecs = 0, bool trigger = false ) :
	  _task(task),
	  _timerInterval(millisecs),
	  _live(false),
	  _timerPool(TimerPool::getInstance())
  {

  }

  CppTimer::~CppTimer()
  {

  }

  void CppTimer::setInterval(long millisecs)
  {
    _timerInterval = boost::posix_time::milliseconds(millisecs);
  }

  void CppTimer::startTimer()
  {
    TimerPool::getInstance().start();
  }

  void CppTimer::stopTimer()
  {
    TimerPool::getInstance().stop();
  }

  void CppTimer::setNextTriggerPointInTime(boost::chrono::time_point pointInTime)
  {
    _nextTriggeringPointInTime = pointInTime;
  }

  void CppTimer::executeTask()
  {
    _task();
  }

}


