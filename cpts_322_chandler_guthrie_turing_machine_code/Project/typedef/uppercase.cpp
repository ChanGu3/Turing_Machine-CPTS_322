//               Module: uppercase
//                 File: uppercase.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             In this method the abstract method in uppercase.h is defined here.
#include "uppercase.h"

#include <string>
using namespace std;




//      Name: Uppercase
//   Purpose: Captialize All Characters In A String
//
// Operation:
//            This method will take a string as an argument and go char by char replacing the variable with all
//            the uppercase characters and return that new string.
string Uppercase(string value)
{
    for(int ind = 0; ind < (int)value.size(); ind++)
    {
        value[ind] = toupper(value[ind]); 
    }
    return value;
}