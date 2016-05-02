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

/*
CppTimer::CppTimer(CppTimerI::Task task, long timerIntervalInMillisecs, bool toRepeat, long startTimerDelayInMillisecs) :
			  _task(task),
			  _timerInterval(timerIntervalInMillisecs),
			  _startDelay(startTimerDelayInMillisecs),
			  _isRepeatitive(toRepeat),
			  _live(false),
			  _timerPool(TimerPool::getInstance())
{
	// A safe Hack to make shared_from_this work when we have no actual shared object for CppTimer
	auto wp = CppTimer::SharedPtr(this, [](CppTimer*){});
	_timerPool.registerTimer(shared_from_this());
}

void CppTimer::stopTimer()
{
	// A safe Hack to make shared_from_this work when we have no actual shared object for CppTimer
	auto wp = CppTimer::SharedPtr(this, [](CppTimer*){});
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
*/

}


