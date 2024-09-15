//               Module: states
//                 File: states.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module defines all the methods within the class states in the .h file.
//             Every method within this module is all to prepare and use the states in the
//             application.
#include "states.h"

#include "../typedef/uppercase.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//      Name: Load
//   Purpose: Read The States Portion Of The Definition File To Import Into Application
//
// Operation:
//            This method will read in each state until it reaches the keyword INPUT_ALPHABET.
//            Any illegal character in state, existing state, or no states will give an error 
//            and set the application turing machine defintiion in a invalid state. If the keyword
//            INPUT_ALPHABET is not foud it will also set it to an invalid state  
    void states::Load(ifstream &definition, bool valid, bool &invalid_Continue)
    {
        string value;
        bool isDone = false;
        while( (definition >> value) && (Uppercase(value) != "INPUT_ALPHABET:") && isDone == false)
        {   

            for(int ind = 0; ind < (int)value.size() && isDone == false; ind++)
            {
                if( (value[ind] != '\\') &&
                    (value[ind] != '[') && (value[ind] != ']')    &&
                    (value[ind] != '<') && (value[ind] != '>')    &&
                    (value[ind] >= '!') && (value[ind] <= '~')
                  )
                {
                    if( (ind+1) == (int)value.size() )
                    {
                        if(this->Is_Element(value))
                        {
                            cout << value << " Already Exists In States" << "\n";
                            invalid_Continue = true;
                            ind = (int)value.size();
                        }
                        else
                        {
                            this->names.push_back(value);
                        }
                        
                    }
                }
                else
                {
                    cout << "Illegal Character In State " << value << "\n";
                    invalid_Continue = true; 
                    ind = (int)value.size();
                }
            }
        }
        
        if(this->names.size() == 0)
        {
            cout << "There Are No States\n";
            invalid_Continue = true; 
        }
        if( (Uppercase(value) != "INPUT_ALPHABET:") )
        {
            cout << "Missing Keyword After States.\n";
            valid = false;
        }

        return;
    }

//      Name: View
//   Purpose: Display All States In A Formal Matter
    void states::View()
    {
        cout << "Q = {";
        for(int i = 0; i < (int)this->names.size(); i++)
        {
            cout << this->names[i]; 
            if((i+1) < (int)this->names.size()){ cout << ", "; }
        }
        cout << "}" << "\n";
        return;
    } 

//      Name: Is_Element
//   Purpose: Check If A State Is Within States
//
// Operation:
//            Return true or false depending if the value parameter is is within the states
    bool states::Is_Element(string value)
    {
        for(int i = 0; i < (int)this->names.size(); i++)
        {
            if(value == this->names[i])
            {
                return true;
            }   
        }

        return false;
    }