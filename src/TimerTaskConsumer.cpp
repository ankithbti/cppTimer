/*
 * TimerTaskConsumer.cpp
 *
 *  Created on: 28-Apr-2016
 *      Author: ankithbti
 */

#include <cppTimer/TimerTaskConsumer.hpp>

namespace cppTimer
{
/*
TimerTaskConsumer::TimerTaskConsumer(int noOfConsumers)
{
	std::cout << " No of Consumer Threads: " << noOfConsumers << std::endl;
	for(int i = 0 ; i < noOfConsumers ; ++i)
	{
		_consumerThreadGroup.create_thread(boost::bind(&TimerTaskConsumer::executeTask, this));
	}
}

void TimerTaskConsumer::addTask(CppTimer::Task task)
{
	boost::unique_lock<boost::mutex> lock(_qMutex);
	_taskQ.push(task);
	_qCondVar.notify_one();
}

void TimerTaskConsumer::executeTask()
{
	while(true)
	{
		CppTimer::Task task;
		{
			boost::unique_lock<boost::mutex> lock(_qMutex);
			while(_taskQ.size() == 0)
			{
				// Release lock and Wait unless we have any entry
				_qCondVar.wait(lock);
			}
			// Take out entry from Q - TODO - could be fetched in bulk - may be in future we can implement that
			task = _taskQ.front();
			_taskQ.pop();
		}
		task();
	}
}
*/
}

