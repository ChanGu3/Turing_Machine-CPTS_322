//               Module: input_alphabet
//                 File: input_alphabet.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module defines all the methods within the class input_alphabet in the .h file.
//             Every method within this module is all to prepare and use the input alphabet in the
//             application.
#include "input_alphabet.h"

#include "../typedef/uppercase.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

//      Name: input_alphabet
//   Purpose: Initalize Objects Of Class
    input_alphabet::input_alphabet(tape_alphabet *TA)
    {
        this->TA = TA;
    }

//      Name: Load
//   Purpose: Read The Input Alphabet Portion Of The Definition File To Import Into Application 
//
// Operation:
//           This method will read in each input alphabet character until it reaches the keyword TAPE_ALPHABET.
//           Any illegal character, existing character, will give an error and set the application turing machine 
//           defintiion in a invalid state. If keyword is missing after this data it is also in a invalid state.
    void input_alphabet::Load(ifstream &definition, bool &valid, bool &invalid_Continue)
    {
        string value;
        while( (definition >> value) && (Uppercase(value) != "TAPE_ALPHABET:") )
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
                cout << value << " Illegal Input_Alphabet Character.\n";
                invalid_Continue = true; 
            }
        }
        
        if( (Uppercase(value) != "TAPE_ALPHABET:") )
        {
            cout << "Missing Keyword After Input_Alphabet.\n";
            valid = false;
        }
        return;
    } 

//      Name: Validate
//   Purpose: Check Characters In Input Alphabet To Be In Tape Alphabet
//
// Operation: This method will check each charactere in input alphabet and make sure the character is within 
//            the tape alphabet using a method within that class. If at least one is not apart of the states 
//            an error will be provided and set the application turing machine defintiion in a invalid state.
    void input_alphabet::Validate(bool &invalid_Continue)
    {
        for(int i = 0; i < (int)this->alphabet.size(); i++)
        {
            if(!this->TA->Is_Element(this->alphabet[i]))
            {
                cout << "The Character " << this->alphabet[i] << " In The Input Alphabet, " << "Is Not In The Tape Alphabet.\n";
                invalid_Continue = true;  
            }
        }
        return;
    } 

//      Name: View
//   Purpose: Display A Formal Definition Of the Input Alphabet
    void input_alphabet::View()
    {
        cout << "sigma = {";
        for(int i = 0; i < (int)this->alphabet.size(); i++)
        {
            cout << this->alphabet[i]; 
            if((i+1) < (int)this->alphabet.size()){ cout << ", "; }
        }
        cout << "}" << "\n";
        return;
    } 

//      Name: Is_Element
//   Purpose: Check If A Character Is Within The Input Alphabet
//
// Operation:
//            Return true or false depending if the value parameter is is within the input alphabet
    bool input_alphabet::Is_Element(char value)
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