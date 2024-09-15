//               Module: final_states_header
//                 File: final_states.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module holds the class defintion for final states with its objects and methods.  
#ifndef FINAL_STATES_H

#define FINAL_STATES_H

#include "states.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class final_states{
private:
    vector<string> names = {};

    states *S;
public:
    final_states(states *S);
    void Load(ifstream &definition, bool &valid, bool &invalid_Continue);
    void Validate(bool &invalid_Continue);
    void View(); 
    bool Is_Element(string value);
};

#endif