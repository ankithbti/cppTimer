/*
 * TimerTaskConsumer.hpp
 *
 *  Created on: 28-Apr-2016
 *      Author: ankithbti
 */

#ifndef INCLUDE_CPPTIMER_TIMERTASKCONSUMER_HPP_
#define INCLUDE_CPPTIMER_TIMERTASKCONSUMER_HPP_


#include <cppTimer/CommonHeaders.hpp>
#include <cppTimer/CppTimer.hpp>

namespace cppTimer
{
class TimerTaskConsumer : private boost::noncopyable
{
public:
	typedef boost::shared_ptr<TimerTaskConsumer> SharedPtr;
	typedef std::queue<CppTimerI::Task> TaskQ;

	void executeTask();

private:
	TaskQ _taskQ;
	boost::thread_group _consumerThreadGroup;
	boost::mutex _qMutex;
	boost::condition_variable _qCondVar;

public:
	TimerTaskConsumer(int noOfConsumers = 1);

	void addTask(typename CppTimerI::Task task);

};
}


#endif /* INCLUDE_CPPTIMER_TIMERTASKCONSUMER_HPP_ */
