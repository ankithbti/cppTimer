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
	//std::function< typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));
	//typedef boost::function<typename std::result_of<Callable(VarArgs...)>::type(VarArgs...)> Task;
	//typedef typename std::function<typename std::result_of<Callable(VarArgs...)>::type(VarArgs...)> Task;
	typedef std::function<void()> Task;

	virtual void stopTimer() = 0;
	virtual const boost::chrono::milliseconds& getInterval() const = 0;
	virtual const boost::chrono::milliseconds& getStartDelay() const = 0;
	virtual bool getStatus() const = 0;
	virtual bool isRepeatitive() const = 0;

	virtual ~CppTimerI(){

	}

};
}




#endif /* INCLUDE_CPPTIMER_CPPTIMERI_HPP_ */
