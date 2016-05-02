/*
 * PoolTimer.hpp
 *
 *  Created on: 26-Apr-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_CPPTIMER_CPPTIMER_HPP_
#define INCLUDE_CPPTIMER_CPPTIMER_HPP_

#include <cppTimer/CommonHeaders.hpp>
#include <cppTimer/CppTimerI.hpp>

namespace cppTimer
{

template <typename R, typename... T>
class Callback
{
public:
	Callback(R (*f)(T...)) { _f = f; }
	R operator()(T... args) {return _f(args...);}

private:
	R (*_f)(T...);

};


template<typename... T>
class TimerPool;

template<typename... T>
struct TimerComparator;

template<typename... Args>
class CppTimer : public CppTimerI<Args...> , public boost::enable_shared_from_this<CppTimer<Args...> >
{
public:
	typedef boost::shared_ptr<CppTimer<Args...> > SharedPtr;
private:
	typename CppTimerI<Args...>::Task _task;
	boost::chrono::milliseconds _timerInterval;
	boost::chrono::milliseconds _startDelay;
	boost::chrono::system_clock::time_point _nextTriggeringPointInTime;
	volatile bool _isRepeatitive;
	volatile bool _live;
	TimerPool<Args...>& _timerPool;

	Callback<void, Args...> _callback;

	friend class TimerPool<Args...>;
	friend struct TimerComparator<Args...>;

	void setNextTriggerPointInTime(boost::chrono::system_clock::time_point pointInTime)
	{
		_nextTriggeringPointInTime = pointInTime;
	}

	const boost::chrono::system_clock::time_point& getNextTriggerPointInTime() const
	{
		return _nextTriggeringPointInTime;
	}

	void setStatus(bool status)
	{
		_live = status;
	}

	void executeTask()
	{
		_task();
	}

public:
	CppTimer(typename CppTimerI<Args...>::Task task, long timerIntervalInMillisecs, bool toRepeat = false, long startTimerDelayInMillisecs = 0) :
		_task(task),
		_timerInterval(timerIntervalInMillisecs),
		_startDelay(startTimerDelayInMillisecs),
		_isRepeatitive(toRepeat),
		_live(false),
		_timerPool(TimerPool<Args...>::getInstance())
{
		// A safe Hack to make shared_from_this work when we have no actual shared object for CppTimer
		auto wp = CppTimer::SharedPtr(this, [](CppTimer*){});
		_timerPool.registerTimer(this->shared_from_this());
}

	virtual void stopTimer()
	{
		// A safe Hack to make shared_from_this work when we have no actual shared object for CppTimer
		auto wp = CppTimer::SharedPtr(this, [](CppTimer*){});
		_timerPool.unregisterTimer(this->shared_from_this());
	}

	virtual const boost::chrono::milliseconds& getInterval() const
	{
		return _timerInterval;
	}

	virtual const boost::chrono::milliseconds& getStartDelay() const
	{
		return _startDelay;
	}

	virtual bool getStatus() const
	{
		return _live;
	}

	virtual bool isRepeatitive() const {
		return _isRepeatitive;
	}

};
}



#endif /* INCLUDE_CPPTIMER_CPPTIMER_HPP_ */
