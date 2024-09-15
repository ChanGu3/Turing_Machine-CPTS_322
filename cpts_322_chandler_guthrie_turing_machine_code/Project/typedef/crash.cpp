//               Module: crash
//                 File: crash.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             In this module the constructor for the crash class uses the constructor of the 
//             runtime_error class to call the exception.  
#include "crash.h"

#include <stdexcept>
#include <string>
using namespace std;

//      Name: crash
//   Purpose: handle exceptions
//
// Operation:
//            calls the constructor within its inherited class runtime_error to 
//            intialize this type of exeception with an error chosen by the developer. 
crash::crash(string reason, bool leftCrash): runtime_error(reason.c_str())
{
       this->leftCrash = leftCrash;
}

//      Name: getLeftCrash
//   Purpose: Returns The Value Of the LeftCrash Object Within This Class
bool crash::getLeftCrash()
{
    return this->leftCrash;
}

