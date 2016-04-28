/*
 * CppTimer.hpp
 *
 *  Created on: 22-Apr-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_CPPTIMER_CPPTIMERI_HPP_
#define INCLUDE_CPPTIMER_CPPTIMERI_HPP_

#include <cppTimer/CommonHeaders.hpp>

namespace cppTimer
{
  class CppTimerI : private boost::noncopyable
  {

  public:
    typedef boost::shared_ptr<CppTimerI> SharedPtr;
    typedef boost::function<void()> Task;


    virtual void startTimer(long millisecs, bool toRepeat = true) = 0;
    virtual void stopTimer() = 0;
    virtual const boost::chrono::milliseconds& getInterval() const = 0;

    virtual ~CppTimerI(){

    }

  };
}




#endif /* INCLUDE_CPPTIMER_CPPTIMERI_HPP_ */
