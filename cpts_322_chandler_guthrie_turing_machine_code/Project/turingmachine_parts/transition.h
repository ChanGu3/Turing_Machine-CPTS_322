//               Module: transition_header
//                 File: transition.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//              This module holds the class defintion for transition with its objects and methods.
#ifndef TRANSITION_H
#define TRANSITION_H

#include "../typedef/direction_t.h"
#include <string>
using namespace std;

class transition{
private:
    string source; 
    char read; 
    string destination; 
    char write;
    direction move; 
public:
    transition(string source_State, 
               char read_Character, 
               string destination_State, 
               char write_Character, 
               direction move_Direction);

    string Source_State(); 
    char Read_Character(); 
    string Destination_State(); 
    char Write_Character(); 
    direction Move_Direction();

};

#endif