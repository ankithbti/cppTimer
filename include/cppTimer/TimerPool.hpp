/*
 * TimerPool.hpp
 *
 *  Created on: 27-Apr-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_CPPTIMER_TIMERPOOL_HPP_
#define INCLUDE_CPPTIMER_TIMERPOOL_HPP_

#include <cppTimer/CommonHeaders.hpp>
#include <cppTimer/TimerTaskConsumer.hpp>
#include <cppTimer/CppTimer.hpp>

namespace cppTimer
{
// TODO - May be in future we can take this from some config file in TimePool
const int NO_OF_TASK_CONSUMER_THREADS = 1;

template<typename... Args>
struct TimerComparator
{
	bool operator()(boost::shared_ptr<CppTimer<Args...> > timer1, boost::shared_ptr<CppTimer<Args...> > timer2)
	{
		return timer1->getNextTriggerPointInTime() < timer2->getNextTriggerPointInTime();
	}
};

template<typename... Args>
class TimerPool : private boost::noncopyable
{

public:
	typedef boost::shared_ptr<TimerPool<Args...> > SharedPtr;
	typedef std::set<boost::shared_ptr<CppTimer<Args...> >, TimerComparator<Args...> > Timers;
	typedef typename Timers::iterator TimersIt;
	typedef typename Timers::const_iterator TimersConstIt;

private:

	boost::shared_ptr<boost::thread> _poolMaintainerThread;
	Timers _timers;
	mutable boost::mutex _timersMutex;
	boost::condition_variable _timersCondVar;
	boost::chrono::system_clock::time_point _currTimePoint;
	volatile bool _isRunning;
	boost::shared_ptr<TimerTaskConsumer<Args...> > _taskConsumer;

	void start()
	{
		boost::unique_lock<boost::mutex> lock (_timersMutex);
		if (!_isRunning)
		{
			_isRunning = true;
			_poolMaintainerThread = boost::shared_ptr<boost::thread> (
					new boost::thread (boost::bind (&TimerPool::loopTimers, this)));
			_taskConsumer = boost::shared_ptr<TimerTaskConsumer<Args...> >(new TimerTaskConsumer<Args...>(NO_OF_TASK_CONSUMER_THREADS));
		}
	}

	void stop()
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

	void loopTimers()
	{
		while (_isRunning)
		{
			boost::unique_lock<boost::mutex> lock (_timersMutex);

			_currTimePoint = boost::chrono::system_clock::now ();

			if (_timers.size () > 0 && ((*_timers.begin ())->getNextTriggerPointInTime () <= _currTimePoint))
			{
				boost::shared_ptr<CppTimer<Args...> > oldTimer (*_timers.begin ());
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


	void executeTask(boost::shared_ptr<CppTimer<Args...> > timer)
	{
		timer->executeTask ();
	}

public:
	static TimerPool& getInstance();
	void registerTimer(boost::shared_ptr<CppTimer<Args...> > timer)
	{
		boost::unique_lock<boost::mutex> lock (_timersMutex);
		_timers.insert (timer);
		_currTimePoint = boost::chrono::system_clock::now ();
		timer->setNextTriggerPointInTime (_currTimePoint + timer->getInterval () + timer->getStartDelay ());
		_timersCondVar.notify_one ();
	}

	void unregisterTimer(boost::shared_ptr<CppTimer<Args...> > timer)
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
	bool isRunning() const
	{
		boost::unique_lock<boost::mutex> lock (_timersMutex);
		return _isRunning;
	}

private:
	TimerPool() : _isRunning (false)
{
		start ();
}
};
}



#endif /* INCLUDE_CPPTIMER_TIMERPOOL_HPP_ */
