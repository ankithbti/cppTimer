#include<iostream>
#include <cppTimer/CppTimer.hpp>

struct TaskStruct{
  int _i;
  boost::posix_time::ptime _prev;
  TaskStruct(int i) : _i(i){

  }

  void myTask()
  {
    std::cout << boost::posix_time::microsec_clock::local_time();
    if(_prev.is_not_a_date_time()){
	_prev = boost::posix_time::microsec_clock::local_time();
    }else{
	boost::posix_time::time_duration gap = boost::posix_time::microsec_clock::local_time() - _prev;
	 std::cout << " | " << gap.total_milliseconds() ;
	_prev = boost::posix_time::microsec_clock::local_time();
    }
    std::cout << " ::  My Task - " << _i << std::endl;
  }
};

int main()
{
  std::cout << " Hello Timer" << std::endl;

  int timercount = 10;
  std::vector<cppTimer::CppTimerI::SharedPtr> timers;
  std::vector<TaskStruct> taskStructs;

  for( int i = 0; i < timercount; i++ )
    {
      TaskStruct ts(i);
      taskStructs.push_back(ts);
    }

  // Creating timers - multiple
  for( int i = 0; i < timercount; i++ )
    {
      cppTimer::CppTimerI::SharedPtr timer(new cppTimer::CppTimer(boost::bind(&TaskStruct::myTask, &taskStructs.at(i))));
      if((i%2) == 0){
	  // Even will only fire 1 time
	  timer->startTimer(3000, false);
      }else{
	  // Odd will fire in repeat fashion
	  if( i > 5 ){
	      timer->startTimer(1000);
	  }else{
	      timer->startTimer(2000);
	  }


      }
      timers.push_back(timer);
    }


  boost::this_thread::sleep(boost::posix_time::milliseconds(20000));
  for( int i = 0; i < timercount; i++ )
    {
      timers.at(i)->stopTimer();
    }


  std::cout << " Stopped all" << std::endl;

  boost::this_thread::sleep(boost::posix_time::milliseconds(5000));
  std::cout << " Exiting." << std::endl;

  return 0;
}
