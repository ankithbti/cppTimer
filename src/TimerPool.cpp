/*
 * TimerPool.cpp
 *
 *  Created on: 27-Apr-2016
 *      Author: ankithbti
 */

#include <cppTimer/TimerPool.hpp>

namespace cppTimer
{

/*
TimerPool::TimerPool () :
						  _isRunning (false)
{
	start ();
}

TimerPool&
TimerPool::getInstance ()
{
	static TimerPool timerPool;
	return timerPool;
}

void
TimerPool::start ()
{
	boost::unique_lock<boost::mutex> lock (_timersMutex);
	if (!_isRunning)
	{
		_isRunning = true;
		_poolMaintainerThread = boost::shared_ptr<boost::thread> (
				new boost::thread (boost::bind (&TimerPool::loopTimers, this)));
		_taskConsumer = TimerTaskConsumer::SharedPtr (new TimerTaskConsumer (NO_OF_TASK_CONSUMER_THREADS));
	}
}

void
TimerPool::stop ()
{
	boost::unique_lock<boost::mutex> lock (_timersMutex);
	if (_isRunning)
	{
		_isRunning = false;
		_timersCondVar.notify_one ();
	}
	_poolMaintainerThread->join ();
	_poolMaintainerThread.reset ();
	_taskConsumer.reset ();
}

bool
TimerPool::isRunning () const
{
	boost::unique_lock<boost::mutex> lock (_timersMutex);
	return _isRunning;
}

void
TimerPool::registerTimer (CppTimer::SharedPtr timer)
{
	boost::unique_lock<boost::mutex> lock (_timersMutex);
	_timers.insert (timer);
	_currTimePoint = boost::chrono::system_clock::now ();
	timer->setNextTriggerPointInTime (_currTimePoint + timer->getInterval () + timer->getStartDelay ());
	_timersCondVar.notify_one ();
}

void
TimerPool::unregisterTimer (CppTimer::SharedPtr timer)
{
	boost::unique_lock<boost::mutex> lock (_timersMutex);
	for (TimersConstIt it = _timers.begin (); it != _timers.end (); ++it)
	{
		if ((*it).get () == timer.get ())
		{
			_timers.erase (it);
			break;
		}
	}
	_timersCondVar.notify_one ();
}

void
TimerPool::loopTimers ()
{
	while (_isRunning)
	{
		boost::unique_lock<boost::mutex> lock (_timersMutex);

		_currTimePoint = boost::chrono::system_clock::now ();

		if (_timers.size () > 0 && ((*_timers.begin ())->getNextTriggerPointInTime () <= _currTimePoint))
		{
			CppTimer::SharedPtr oldTimer (*_timers.begin ());
			oldTimer->setNextTriggerPointInTime (_currTimePoint + oldTimer->getInterval ());

			// Send this task to TimerTaskConsumer for further processing
			_taskConsumer->addTask (boost::bind (&TimerPool::executeTask, this, oldTimer));

			// Delete the old entry and again add the entry again, so that our entries
			// in set should be sorted on basis of nextTriggerPoint
			_timers.erase (_timers.begin ());
			_timers.insert (oldTimer);
			if (!oldTimer->isRepeatitive ())
			{
				_timers.erase (_timers.find (oldTimer));
			}

		}

		boost::chrono::system_clock::time_point tillTime;
		if (_timers.size () > 0)
		{
			tillTime = (*(_timers.begin ()))->getNextTriggerPointInTime ();

		}
		else
		{
			tillTime = _currTimePoint + boost::chrono::milliseconds (10);
		}
		_timersCondVar.wait_until (lock, tillTime);
	}
}

void
TimerPool::executeTask (CppTimer::SharedPtr timer)
{
	timer->executeTask ();
}

*/
}

