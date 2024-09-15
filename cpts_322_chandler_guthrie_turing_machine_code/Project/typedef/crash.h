//               Module: crash_header
//                 File: crash.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module holds the class defintion for crash with its new object and methods. crash inherits all 
//             the objects and methods from the runtime_error class that provides exception handling with a error 
//             during runtime such as running out of memory. 
#ifndef CRASH_H
#define CRASH_H

#include <stdexcept>
#include <string>
using namespace std;

class crash: public runtime_error
{
private:
    bool leftCrash = false;
public:
    crash(string reason, bool leftCrash);
    bool getLeftCrash();
};

#endif