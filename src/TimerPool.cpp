/*
 * TimerPool.cpp
 *
 *  Created on: 27-Apr-2016
 *      Author: ankithbti
 */

#include <cppTimer/TimerPool.hpp>

namespace cppTimer
{

  TimerPool::TimerPool() : _isRunning(false)
  {
    start();
  }

  TimerPool::~TimerPool()
  {
    stop();
  }

  TimerPool& TimerPool::getInstance()
  {
    static TimerPool timerPool;
    return timerPool;
  }

  void TimerPool::start()
  {
    boost::unique_lock<boost::mutex> lock(_timersMutex);
    if(!_isRunning)
      {
	_isRunning = true;
	_poolMaintainerThread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&TimerPool::loopTimers, this)));
      }
  }

  void TimerPool::stop()
  {
    boost::unique_lock<boost::mutex> lock(_timersMutex);
    if(_isRunning)
      {
	_isRunning = false;
	_timersCondVar.notify_one();
      }
    _poolMaintainerThread->join();
  }

  void TimerPool::registerTimer(CppTimer::SharedPtr timer)
  {
    boost::unique_lock<boost::mutex> lock(_timersMutex);
    _timers.insert(timer);
    _currTimePoint = boost::chrono::system_clock::now();
    timer->setNextTriggerPointInTime(_currTimePoint + timer->getInterval());
    _timersCondVar.notify_one();
  }

  void TimerPool::unregisterTimer(CppTimer::SharedPtr timer)
  {
    boost::unique_lock<boost::mutex> lock(_timersMutex);
    for(TimersConstIt it = _timers.begin() ; it != _timers.end() ; ++it)
      {
	if((*it).get() == timer.get())
	  {
	    _timers.erase(it);
	    break;
	  }
      }
    _timersCondVar.notify_one();
  }

  void TimerPool::loopTimers()
  {
    while(_isRunning)
      {
	boost::unique_lock<boost::mutex> lock(_timersMutex);
	_currTimePoint = boost::chrono::system_clock::now();

	for(TimersConstIt it = _timers.begin() ; it != _timers.end() ; ++it)
	  {
	    if((*it)->getNextTriggerPointInTime() <= _currTimePoint)
	      {
		(*it)->setNextTriggerPointInTime(_currTimePoint + (*it)->getInterval());
		boost::thread taskThread(boost::bind(&TimerPool::executeTask, this, (*it)));
		taskThread.detach();
	      }else{
		  // as our list is already sorted based upon nextTriggerPointInTime
		  break;
	      }
	  }

	boost::chrono::time_point tillTime;
	if(_timers.size() > 0)
	  {
	    tillTime = (*(_timers.begin()))->getNextTriggerPointInTime();

	  }else{
	      tillTime = boost::chrono::milliseconds(1000);
	  }
	_timersCondVar.wait(lock, tillTime);
      }
  }

  void TimerPool::executeTask(CppTimer::SharedPtr timer)
  {
    timer->executeTask();
  }
}


