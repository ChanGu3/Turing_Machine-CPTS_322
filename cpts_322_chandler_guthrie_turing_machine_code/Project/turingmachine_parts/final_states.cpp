//               Module: final_states
//                 File: final_states.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module defines all the methods within the class final_state in the .h file.
//             Every method within this module is all to prepare and use the final states in the
//             application.
#include "final_states.h"

#include "states.h"
#include "../typedef/uppercase.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//      Name: final_states 
//   Purpose: Initialize objects
    final_states::final_states(states *S)
    {
        this->S = S;
    }

//      Name: Load
//   Purpose: Read The Final States Portion Of The Definition File To Import Into Application
//
// Operation:
//            This method will read in each final state until it reaches the end of the file
//            Any illegal character in state or existing state will give an error 
//            and set the application turing machine definition in a invalid state.  
    void final_states::Load(ifstream &definition, bool &valid, bool &invalid_Continue)
    {
        string value;
        bool isDone = false;
        while( (definition >> value) && isDone == false)
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
                            cout << value << " Already Exists In Final_States" << "\n";
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
        

        return;
    }

//      Name: Validate
//   Purpose: Check All Final States To Be In States
//
// Operation: This method will check each final state and make sure its within 
//            all the states using a method within the class. If at least one
//            is not apart of the states an error will be provided and set the 
//            application turing machine defintiion in a invalid state.
    void final_states::Validate(bool &invalid_Continue)
    {
        for(string value: this->names)
        {
            if(!S->Is_Element(value))
            {
                cout << "Final_State " << value << " Is Not In States" << "\n";
                invalid_Continue = true; 
            }
        }
    }

//      Name: View
//   Purpose: Display All Final States In A Formal Matter
    void final_states::View()
    {
        cout << "F = {";
        for(int i = 0; i < (int)this->names.size(); i++)
        {
            cout << this->names[i]; 
            if((i+1) < (int)this->names.size()){ cout << ", "; }
        }
        cout << "}" << "\n";
        return;
    } 

//      Name: Is_Element
//   Purpose: Check If A State Is Within Final States
//
// Operation:
//            Return true or false depending if the value parameter is is within the final states
    bool final_states::Is_Element(string value)
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
