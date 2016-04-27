#include<iostream>
#include <cppTimer/CppTimer.hpp>

struct TaskStruct{
  int _i;
  TaskStruct(int i) : _i(i){

  }

  void myTask()
  {
    boost::posix_time::ptime now ( boost::posix_time::second_clock::local_time());
    std::cout << now << " ::  My Task - " << _i << std::endl;
  }
};

int main()
{
  std::cout << " Hello Timer" << std::endl;

  int timercount = 2;
  std::vector<cppTimer::CppTimerI::SharedPtr> timers;
  std::vector<TaskStruct> taskStructs;

  for( int i = 0; i < timercount; i++ )
    {
      TaskStruct ts(i);
      taskStructs.push_back(ts);
    }

  //  for( int i = 0; i < timercount; i++ )
  //    {
  //      cppTimer::CppTimerI::SharedPtr timer(new cppTimer::CppTimer(boost::bind(&TaskStruct::myTask, &taskStructs.at(i))));
  //
  //      timer->startTimer(5000);
  //      timers.push_back(timer);
  //    }

  cppTimer::CppTimerI::SharedPtr timer(new cppTimer::CppTimer(boost::bind(&TaskStruct::myTask, &taskStructs.at(0))));
  timer->startTimer(5000);
  timers.push_back(timer);

  sleep(1);

  cppTimer::CppTimerI::SharedPtr timer1(new cppTimer::CppTimer(boost::bind(&TaskStruct::myTask, &taskStructs.at(1))));
    timer1->startTimer(2000);
    timers.push_back(timer1);

  boost::this_thread::sleep(boost::posix_time::milliseconds(20000));
  for( int i = 0; i < timercount; i++ )
    {
      timers.at(i)->stopTimer();
    }


  std::cout << " Stopped all" << std::endl;

  boost::this_thread::sleep(boost::posix_time::milliseconds(5000));
  std::cout << " Exiting." << std::endl;
  //  {
  //    cppTimer::CppTimerI::SharedPtr timer(new cppTimer::CppTimer(boost::bind(&myTask)));
  //    timer->startTimer(1000);
  //
  //
  //    boost::this_thread::sleep(boost::posix_time::milliseconds(10000));
  //    timer->stopTimer();
  //    boost::this_thread::sleep(boost::posix_time::milliseconds(5000));
  //  }

  return 0;
}
