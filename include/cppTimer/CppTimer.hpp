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

  class CppTimer : public CppTimerI
  {
  public:
    typedef boost::shared_ptr<CppTimer> SharedPtr;
  private:
    CppTimerI::Task _task;
    boost::posix_time::milliseconds _timerInterval;
    boost::chrono::time_point _nextTriggeringPointInTime;
    volatile bool _live;
    TimerPool& _timerPool;

    friend TimerPool;

    void setNextTriggerPointInTime(boost::chrono::time_point pointInTime);

    const boost::chrono::time_point& getNextTriggerPointInTime() const
    {
      return _nextTriggeringPointInTime;
    }

    void executeTask();

  public:
    CppTimer(CppTimerI::Task task, long millisecs = 0, bool trigger = false );
    ~CppTimer();

    virtual void setInterval(long millisecs);
    virtual void startTimer();
    virtual void stopTimer();

    virtual long getInterval() const
    {
      return _timerInterval;
    }

  };
}



#endif /* INCLUDE_CPPTIMER_CPPTIMER_HPP_ */
