//               Module: transition_function_header
//                 File: transition_function.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//              This module holds the class defintion for transition_function with its objects and methods.
#ifndef TRANSITION_FUNCTION_H
#define TRANSITION_FUNCTION_H

#include "transition.h"
#include "tape_alphabet.h"
#include "states.h"
#include "final_states.h"
#include "../typedef/direction_t.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class transition_function{
private:
    vector<transition> transitions;
    tape_alphabet *TA; 
    states *S;
    final_states *FS;
public:
    transition_function(tape_alphabet *TA, states *S, final_states *FS);
    void Load(ifstream &definition, bool &valid, bool &invalid_Continue); 
    void Validate(bool &invalid_Continue); 
    void View(); 
    void Find_Transition(string source_State, 
                         char read_Character, 
                         string &destination_State, 
                         char &write_Character, 
                         direction &move_Direction, 
                         bool &found); 
    bool IsElement(transition value);
};







#endif