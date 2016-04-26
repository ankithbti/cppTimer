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
  class CppTimerI : boost::noncopyable
  {

  public:
    typedef boost::shared_ptr<CppTimerI> SharedPtr;
    typedef boost::function<void()> Task;

//    CppTimerI(boost::function<void()>, long millisecs = 0, bool trigger = false );
//    ~CppTimerI();


    virtual void setInterval(long millisecs) = 0;
    virtual void startTimer() = 0;
    virtual void stopTimer() = 0;
    virtual long getInterval() const = 0;

    virtual ~CppTimerI(){

    }

  };
}




#endif /* INCLUDE_CPPTIMER_CPPTIMERI_HPP_ */
