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
template<typename... Args>
class TimerTaskConsumer : private boost::noncopyable
{
public:
	typedef boost::shared_ptr<TimerTaskConsumer<Args...> > SharedPtr;
	typedef std::queue<typename CppTimerI<Args...>::Task> TaskQ;

	void executeTask()
	{
		while(true)
		{
			typename CppTimerI<Args...>::Task task;
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

private:
	TaskQ _taskQ;
	boost::thread_group _consumerThreadGroup;
	boost::mutex _qMutex;
	boost::condition_variable _qCondVar;

public:
	TimerTaskConsumer(int noOfConsumers = 1)
{
		std::cout << " No of Consumer Threads: " << noOfConsumers << std::endl;
		for(int i = 0 ; i < noOfConsumers ; ++i)
		{
			_consumerThreadGroup.create_thread(boost::bind(&TimerTaskConsumer::executeTask, this));
		}
}

	void addTask(typename CppTimerI<Args...>::Task task)
	{
		boost::unique_lock<boost::mutex> lock(_qMutex);
		_taskQ.push(task);
		_qCondVar.notify_one();
	}

};
}


#endif /* INCLUDE_CPPTIMER_TIMERTASKCONSUMER_HPP_ */
