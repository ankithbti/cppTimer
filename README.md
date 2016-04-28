# cppTimer

# Build
## Prerequisite - correct boost install base path set in env variable BOOST_INSTALL_ROOT [ check src/makefile ]
make clean - To clean
make all - To build binary [ make sure you have bin folder created ]
make createlib - To build so library [ make sure you have lib folder created ]

# To Run
as binary - ./bin/appCppTimer
as lib - ./lib/libCppTimer.so

# To Do
### To fix the bug in TimerPool loopTimers related to sleep
### To use Q+consumer concept rather than using the separate thread for each task execution
### To use c++11 variadic template for callback function [ task ]
### To use toRepeat flag in TimerPool
