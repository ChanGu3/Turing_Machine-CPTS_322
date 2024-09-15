//               Module: transition_function
//                 File: transition_function.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module defines all the methods within the class transition_function in the .h file.
//             Every method within this module is all to prepare and use the transitions in the
//             application so that it can update specific states and then characters within the tape. 
#include "transition_function.h"
#include "transition.h"
#include "tape_alphabet.h"
#include "states.h"
#include "final_states.h"
#include "../typedef/direction_t.h"

#include "../typedef/uppercase.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//      Name: transition_function 
//   Purpose: Intialize This classes objects
    transition_function::transition_function(tape_alphabet *TA, states *S, final_states *FS)
    {
        this->TA = TA;
        this->S = S;
        this->FS = FS;
    }

//      Name: Load 
//   Purpose: Read The Transition_Function Portion Of The Definition File To Import Into Application
//
// Operation:
//            This method will create a tranistion including a source state, current character, destination state, write character, and move direction
//            In that exact order. if the file has unexpected descriptors or not enough an error will display and set the  definition file of the 
//            turing machine into an invlaid state. This can also happen when it does not run into the next keyword INITIAL_STATE. If there exists
//            the same exact transition it will also set it to an invalid state. Otherwise if the keyword is found and none of the errors happen then
//            it continues.
    void transition_function::Load(ifstream &definition, bool &valid, bool &invalid_Continue)
    {
        string value;
        bool isDone = false;
        bool error = false;

        string source_State; 
        char read_Character;
        string destination_State;
        char write_Character;
        direction move_Direction;

        int ind;
        do{
            ind = 0;
            while( ind < 5 && error == false && isDone == false)
            {
                if( !(definition >> value) )
                {
                    cout << "Missing/Misplaced Data In Transition_Function.\n";
                    valid = false;
                }
                if( (Uppercase(value) == "INITIAL_STATE:") && ind == 0)
                {
                    isDone = true;
                }
                else if(Uppercase(value) == "INITIAL_STATE:")
                {
                        cout << "Missing/Misplaced Data In Transition_Function.\n";
                        valid = false;
                        error = true;
                        return;
                }

                if(error == false && isDone == false)
                {
                    if(ind == 0){ source_State = value; ind++;}
                    else if(ind == 1){ read_Character = value[0]; ind++;}
                    else if(ind == 2){ destination_State = value; ind++;}
                    else if(ind == 3){ write_Character = value[0]; ind++;}
                    else if(ind == 4){ if( (toupper(value[0]) == 'L' || toupper(value[0]) == 'R') && (int)value.size() == 1){ move_Direction = value[0]; ind++; }else{ cout << value << " Illegal Move Direction\n"; valid = false; isDone = true; error = true;} }
                }
            } 

            if(error == false && isDone == false)
            { 
                if( this->IsElement( transition(source_State, read_Character, destination_State, write_Character, move_Direction) ) )
                { 
                    invalid_Continue = true; 
                    cout << "Transition: delta(" << source_State << ", " << read_Character << ") = (" << destination_State << ", " << write_Character << ", " << move_Direction << ") Already Exists in Transition_Function " << "\n";
                }
                else
                {
                    this->transitions.push_back(transition(source_State, read_Character, destination_State, write_Character, move_Direction)); 
                }
            
            
            } //No need to check first 4 arguments for Illegal with validatity and other classes doign it for this one.
        
        }while( isDone == false && error == false );

        if( (((isDone == false) && (Uppercase(value) != "INITIAL_STATE:")) || ind != 0)  && error == false )
        {
            cout << "Missing Keyword After Transition_Function.\n";
            valid = false;
        }
        return;
    } 

//      Name: Validate 
//   Purpose: Verify If Each Transition Loaded Contains Existing Values In The Application
//
// Operation:
//            This method will check each transitions source state, current character, destination state, write character, and move direction
//            To verify that they exists within there respective data sets and not in others.
    void transition_function::Validate(bool &invalid_Continue)
    {
        for(int ind = 0; ind < (int)this->transitions.size(); ind++)
        {
            if(FS->Is_Element(this->transitions[ind].Source_State()))
            {
                cout << "Source State " << this->transitions[ind].Source_State() << " Is In Final States\n";
                invalid_Continue = true;
            }
            if(!S->Is_Element(this->transitions[ind].Source_State()))
            {
                cout << "Source State " << this->transitions[ind].Source_State() << " Is Not In States\n";
                invalid_Continue = true;
            }
            if(!TA->Is_Element(this->transitions[ind].Read_Character()))
            {
                cout << "Read Character " << this->transitions[ind].Read_Character() << " Is Not In Tape Alphabet\n";
                invalid_Continue = true;
            }
            if(!S->Is_Element(this->transitions[ind].Destination_State()))
            {
                cout << "Destination State " << this->transitions[ind].Destination_State() << " Is Not In States\n";
                invalid_Continue = true;
            }
            if(!TA->Is_Element(this->transitions[ind].Write_Character()))
            {
                cout << "Write Character " << this->transitions[ind].Write_Character() << " Is Not In Tape Alphabet\n";
                invalid_Continue = true;
            }
        }
        return;
    } 

//      Name: View
//   Purpose: Displays A Formal Defintion Of All the Transitions Included In Defintion File 
    void transition_function::View()
    {
        for(int i = 0; i < (int)this->transitions.size(); i++)
        {
            cout << "delta" << "("
                 << this->transitions[i].Source_State() << ", "  
                 << this->transitions[i].Read_Character() << ")"
                 << " = ("
                 << this->transitions[i].Destination_State() << ", "
                 << this->transitions[i].Write_Character() << ", "
                 << this->transitions[i].Move_Direction() << ")" << "\n";
        }

        return;
    } 

//      Name: IsElement
//   Purpose: Checks If A Transition Is Within The Transitions Set(vector)
//
// Operation:
//            returns true or false depending on if their is a match with the parameter and one of the
//            transitions in the set(vector).
    bool transition_function::IsElement(transition value)
    {
        for(transition valueC: this->transitions)
        {
            if(value.Source_State() == valueC.Source_State() &&
               value.Read_Character() == valueC.Read_Character() &&
               value.Destination_State() == valueC.Destination_State() &&
               value.Write_Character() == valueC.Write_Character() &&
               value.Move_Direction() == valueC.Move_Direction()
              )
            {
                return true;
            }
        }

        return false;
    }

//      Name: Find_Transition
//   Purpose: Find A Transition Within The Set(vector) And Return That Transition If It Exists
//
// Operation:
//            This method will use a source state and read character to find a transition with the transitions set(vector)
//            that will return a destination state, write character, and move direction if found and set found to true. 
//            If a transition is not found nothing will be set and found will be set to false.
    void transition_function::Find_Transition(string source_State, 
                         char read_Character, 
                         string &destination_State, 
                         char &write_Character,
                         direction &move_Direction, 
                         bool &found)
    {
        for(int ind = 0; ind < (int)this->transitions.size(); ind++)
        {
            if( (this->transitions[ind].Source_State() == source_State) && this->transitions[ind].Read_Character() == read_Character)
            {
                destination_State = this->transitions[ind].Destination_State();
                write_Character = this->transitions[ind].Write_Character();
                move_Direction = this->transitions[ind].Move_Direction();
                found = true;
                return;
            }
        }
        found = false;
        return;
    } 