//               Module: tape_alphabet_header
//                 File: tape_alphabet.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//              This module holds the class defintion for tape alphabet with its objects and methods.
#ifndef TAPE_ALPHABET_H
#define TAPE_ALPHABET_H

#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class tape_alphabet{
private:
    vector<char> alphabet = {};
public: 
    void Load(ifstream &definition, bool &valid, bool &invalid_Continue); 
    void View(); 
    bool Is_Element(char value);
};





#endif