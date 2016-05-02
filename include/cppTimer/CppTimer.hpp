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



class TimerPool;
struct TimerComparator;

class CppTimer : public CppTimerI , public boost::enable_shared_from_this<CppTimer>
{
public:
	typedef boost::shared_ptr<CppTimer> SharedPtr;
private:
	CppTimerI::Task _task;
	boost::chrono::milliseconds _timerInterval;
	boost::chrono::milliseconds _startDelay;
	boost::chrono::system_clock::time_point _nextTriggeringPointInTime;
	volatile bool _isRepeatitive;
	volatile bool _live;
	TimerPool& _timerPool;

	friend class TimerPool;
	friend struct TimerComparator;

	void setNextTriggerPointInTime(boost::chrono::system_clock::time_point pointInTime);

	const boost::chrono::system_clock::time_point& getNextTriggerPointInTime() const
	{
		return _nextTriggeringPointInTime;
	}

	void setStatus(bool status)
	{
		_live = status;
	}

	void executeTask();

public:
	CppTimer(typename CppTimerI::Task task, long timerIntervalInMillisecs, bool toRepeat = false, long startTimerDelayInMillisecs = 0);

	virtual void stopTimer();

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
