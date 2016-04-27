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
  class TimerPool;
  struct TimerComparator;

  class CppTimer : public CppTimerI, public boost::enable_shared_from_this<CppTimer>
  {
  public:
    typedef boost::shared_ptr<CppTimer> SharedPtr;
  private:
    CppTimerI::Task _task;
    boost::chrono::milliseconds _timerInterval;
    boost::chrono::system_clock::time_point _nextTriggeringPointInTime;
    volatile bool _live;
    TimerPool& _timerPool;
    volatile bool _isRepeatitive;

    friend class TimerPool;
    friend struct TimerComparator;

    void setNextTriggerPointInTime(boost::chrono::system_clock::time_point pointInTime);

    const boost::chrono::system_clock::time_point& getNextTriggerPointInTime() const
    {
      return _nextTriggeringPointInTime;
    }

    void executeTask();

  public:
    CppTimer(CppTimerI::Task task);
    ~CppTimer();

    virtual void startTimer(long millisecs, bool toRepeat = true);
    virtual void stopTimer();

    virtual const boost::chrono::milliseconds& getInterval() const
    {
      return _timerInterval;
    }

    virtual bool isRepeatitive() const {
      return _isRepeatitive;
    }

  };
}



#endif /* INCLUDE_CPPTIMER_CPPTIMER_HPP_ */
