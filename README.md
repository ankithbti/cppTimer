# cppTimer

* A C++ Timer API with milliseconds precision.
* Using boost libraries - thread, posix_time, chrono
* Using TimerPool concept which is completely abstract from the user.
* Easy API to Create, Start and Cancel the timer.
* Timer can be started in two modes - Repeating Timer &amp; Non-Repeating Timer.

## Build
> Prerequisite - Make sure you have correct boost base path set in env variable BOOST_INSTALL_ROOT [ check src/makefile ]

<p>
make clean - To clean
<br>
make all - To build binary [ make sure you have bin folder created ]
<br>
make createlib - To build so library [ make sure you have lib folder created ]
</p>

## To Run
<p>
As binary - ./bin/appCppTimer
<br>
Use lib - ./lib/libCppTimer.so
</p>

## To Do
* To use c++11 variadic template for callback function [ task ]
* Please suggest the improvements. They are always welcome.
