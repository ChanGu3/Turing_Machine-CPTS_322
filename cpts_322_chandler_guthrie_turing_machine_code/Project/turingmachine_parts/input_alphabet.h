//               Module: input_alphabet_header
//                 File: input_alphabet.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//              This module holds the class defintion for input alphabet with its objects and methods.
#ifndef INPUT_ALPHABET_H
#define INPUT_ALPHABET_H

#include "tape_alphabet.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class input_alphabet{
private:
    vector<char> alphabet = {};

    tape_alphabet *TA;
public: 
    input_alphabet(tape_alphabet *TA);
    void Load(ifstream &definition, bool &valid, bool &invalid_Continue); 
    void Validate(bool &invalid_Continue); 
    void View(); 
    bool Is_Element(char value);
};



#endif