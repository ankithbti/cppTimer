/*
 * TimerThread.hpp
 *
 *  Created on: 22-Apr-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_CPPTIMER_TIMERTHREAD_HPP_
#define INCLUDE_CPPTIMER_TIMERTHREAD_HPP_


#include <cppTimer/CommonHeaders.hpp>

class TimerThread : private boost::noncopyable
{
public:
  typedef boost::shared_ptr<TimerThread> SharedPtr;

private:

public:

  void run();

}


#endif /* INCLUDE_CPPTIMER_TIMERTHREAD_HPP_ */
