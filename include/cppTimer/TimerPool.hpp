/*
 * TimerPool.hpp
 *
 *  Created on: 27-Apr-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_CPPTIMER_TIMERPOOL_HPP_
#define INCLUDE_CPPTIMER_TIMERPOOL_HPP_

#include <cppTimer/CommonHeaders.hpp>
#include <cppTimer/CppTimer.hpp>
#include <cppTimer/TimerTaskConsumer.hpp>

namespace cppTimer
{
// TODO - May be in future we can take this from some config file in TimePool
const int NO_OF_TASK_CONSUMER_THREADS = 1;

struct TimerComparator
{
	bool operator()(CppTimer::SharedPtr timer1, CppTimer::SharedPtr timer2)
	{
		return timer1->getNextTriggerPointInTime() < timer2->getNextTriggerPointInTime();
	}
};

class TimerPool : private boost::noncopyable
{

public:
	typedef boost::shared_ptr<TimerPool> SharedPtr;
	typedef std::set<CppTimer::SharedPtr, TimerComparator> Timers;
	typedef Timers::iterator TimersIt;
	typedef Timers::const_iterator TimersConstIt;

private:

	boost::shared_ptr<boost::thread> _poolMaintainerThread;
	Timers _timers;
	mutable boost::mutex _timersMutex;
	boost::condition_variable _timersCondVar;
	boost::chrono::system_clock::time_point _currTimePoint;
	volatile bool _isRunning;
	TimerTaskConsumer::SharedPtr _taskConsumer;

	void start();
	void stop();
	void loopTimers();
	void executeTask(CppTimer::SharedPtr timer);

public:
	static TimerPool& getInstance();
	void registerTimer(CppTimer::SharedPtr timer);
	void unregisterTimer(CppTimer::SharedPtr timer);
	bool isRunning() const;

private:
	TimerPool();
};
}



#endif /* INCLUDE_CPPTIMER_TIMERPOOL_HPP_ */
