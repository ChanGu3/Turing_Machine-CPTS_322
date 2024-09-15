//               Module: tape_header
//                 File: tape.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//              This module holds the class defintion for tape with its objects and methods.
#ifndef TAPE_H
#define TAPE_H

#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "../typedef/direction_t.h"

#include <string>
#include <fstream>
using namespace std;

class tape{
private:
    string cells = "";
    int current_Cell = 0;
    char blank_Character = ' ';

    input_alphabet *IA;
    tape_alphabet *TA;
public:
    tape(input_alphabet *IA, tape_alphabet *TA);
    void Load(ifstream &definition, bool &valid, bool &invalid_Continue);
    void Validate(bool &invalid_Continue);
    void View();
    void Initialize(string input_String);
    void Update(char write_Character, direction move_Direction); 
    string Left(int maximum_Number_Of_Cells);
    string Right(int maximum_Number_Of_Cells);
    char Current_Character();
    bool Is_First_Cell();
};

#endif