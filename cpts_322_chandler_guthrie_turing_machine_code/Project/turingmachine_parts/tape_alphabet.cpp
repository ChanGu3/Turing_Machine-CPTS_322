//               Module: tape_alphaet
//                 File: tape_alphabet.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module defines all the methods within the class tape_alphabet in the .h file.
//             Every method within this module is all to prepare and use the tape alphabet in the
//             application.
#include "tape_alphabet.h"

#include "../typedef/uppercase.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

//      Name: Load
//   Purpose: Read The Tape Alphabet Portion Of The Definition File To Import Into Application 
//
// Operation:
//           This method will read in each tape alphabet character until it reaches the keyword TRANSITION_FUNCTION.
//           Any illegal character, existing character, will give an error and set the application turing machine 
//           defintiion in a invalid state. If keyword is missing after this data it is also in a invalid state.
    void tape_alphabet::Load(ifstream &definition, bool &valid, bool &invalid_Continue)
    {
        string value;
        while( (definition >> value) && (Uppercase(value) != "TRANSITION_FUNCTION:") )
        {   
            if( (value.size() == 1) && (value[0] != '\\') &&
                (value[0] != '[') && (value[0] != ']')    &&
                (value[0] != '<') && (value[0] != '>')    &&
                (value[0] >= '!') && (value[0] <= '~')
            )
            {
                if(this->Is_Element(value[0]))
                {
                    cout << value << " Already Exists in Input Alphabet" << "\n";
                    invalid_Continue = true;
                }
                else
                {
                    this->alphabet.push_back(value[0]);
                }
            }
            else
            {
                cout << "Illegal Tape_Alphabet Character.\n";
                invalid_Continue = true; 
            }
        }
        
        if( (Uppercase(value) != "TRANSITION_FUNCTION:") )
        {
            cout << "Missing Keyword After Tape_Alphabet.\n";
            valid = false;
        }
        return;
    } 

//      Name: View
//   Purpose: Display A Formal Definition Of the Tape Alphabet
    void tape_alphabet::View()
    {
        cout << "gamma = {";
        for(int i = 0; i < (int)this->alphabet.size(); i++)
        {
            cout << this->alphabet[i]; 
            if((i+1) < (int)this->alphabet.size()){ cout << ", "; }
        }
        cout << "}" << "\n";
        return;
    } 

//      Name: Is_Element
//   Purpose: Check If A Character Is Within The Tape Alphabet
//
// Operation:
//            Return true or false depending if the value parameter is is within the tape alphabet
    bool tape_alphabet::Is_Element(char value)
    {
        for(int i = 0; i < (int)this->alphabet.size(); i++)
        {
            if(value == this->alphabet[i])
            {
                return true;
            }   
        }
        return false;
    }