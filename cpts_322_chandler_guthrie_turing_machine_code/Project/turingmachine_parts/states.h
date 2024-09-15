//               Module: states
//                 File: states.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module holds the class defintion for states with its objects and methods.
//             
// 
#ifndef STATES_H
#define STATES_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class states{
private:
    vector<string> names = {};
public:
    void Load(ifstream &definition, bool valid, bool &invalid_Continue);
    void View(); 
    bool Is_Element(string value);

};






#endif