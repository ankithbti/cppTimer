/*
 * CppTimer.cpp
 *
 *  Created on: 27-Apr-2016
 *      Author: ankithbti
 */

#include <cppTimer/CppTimer.hpp>
#include <cppTimer/TimerPool.hpp>

namespace cppTimer
{

  CppTimer::CppTimer(CppTimerI::Task task) :
	  _task(task),
	  _live(false),
	  _timerPool(TimerPool::getInstance())
  {
  }

  CppTimer::~CppTimer()
  {

  }

  void CppTimer::startTimer(long millisecs, bool toRepeat)
  {
    _timerInterval = boost::chrono::duration_cast<boost::chrono::milliseconds>(boost::chrono::milliseconds(millisecs));
    _isRepeatitive = toRepeat;
    _timerPool.registerTimer(shared_from_this());
  }

  void CppTimer::stopTimer()
  {
    _timerPool.unregisterTimer(shared_from_this());
  }

  void CppTimer::setNextTriggerPointInTime(boost::chrono::system_clock::time_point pointInTime)
  {
    _nextTriggeringPointInTime = pointInTime;
  }

  void CppTimer::executeTask()
  {
    _task();
  }

}


