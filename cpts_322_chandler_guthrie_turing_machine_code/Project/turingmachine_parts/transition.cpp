//               Module: transition
//                 File: transition.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module defines all the methods within the class transition in the .h file.
//             Every method within this module is all to prepare and use the transition in the
//             application specifically the transition function.             
#include "transition.h"

#include "../typedef/direction_t.h"
#include <string>
using namespace std;

//      Name: transition
//   Purpose: Initalize Objects Within Class Using Parameters.
    transition::transition(string source_State, 
               char read_Character, 
               string destination_State, 
               char write_Character, 
               direction move_Direction)
    {
        this->source = source_State;
        this->read = read_Character;
        this->destination = destination_State;
        this->write = write_Character;
        this->move = move_Direction;
        return;
    } 

//      Name: Source_State
//   Purpose: Return The Class Object Source State
    string transition::Source_State()
    {
        return this->source;
    }

//      Name: Read_Character
//   Purpose: Return The Class Object Read Character
    char transition::Read_Character()
    {
        return this->read;
    } 

//      Name: Destination_State
//   Purpose: Return The Class Object Destination State
    string transition::Destination_State()
    {
        return this->destination;
    } 

//      Name: Write_Character
//   Purpose: Return The Class Object Write Character
    char transition::Write_Character()
    {
        return this->write;
    } 

//      Name: Move_Direction
//   Purpose: Return The Class Object Move Direction
    direction transition::Move_Direction()
    {
        return this->move;
    }