//               Module: tape
//                 File: tape.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module defines all the methods within the class tape in the .h file.
//             Every method within this module allows for the tape to be modified and created
//             within the application. As well as reading in the blank character to use within
//             the application.
#include "tape.h"
#include "input_alphabet.h"
#include "tape_alphabet.h"
#include "../typedef/direction_t.h"
#include "../typedef/uppercase.h" 
#include "../typedef/crash.h"

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

//      Name: tape
//   Purpose: Initialize objects
    tape::tape(input_alphabet *IA, tape_alphabet *TA)
    {
        this->IA = IA;
        this->TA = TA;
    }

//      Name: Load 
//   Purpose: Read The blank character Portion Of The Definition File To Import Into Application
//
// Operation:
//            This method will read in the blank character and then the keyword FINAL_STATES.
//            Any illegal character will give an error and set the application turing machine 
//            defintiion in a invalid state.             
    void tape::Load(ifstream &definition, bool &valid, bool &invalid_Continue)
    {
        string value;
        if( (definition >> value) &&
            (value.size() == 1) && (value[0] != '\\') &&
            (value[0] != '[') && (value[0] != ']')    &&
            (value[0] != '<') && (value[0] != '>')    &&
            (value[0] >= '!') && (value[0] <= '~')
          )
        {

            this->blank_Character = value[0];
        }
        else
        {
            cout << "Illegal Blank_Character.\n";
            invalid_Continue = true; 
        }
        if( !(definition >> value) || (Uppercase(value) != "FINAL_STATES:") )
        {
            cout << "Missing Keyword After Blank_Character.\n";
            valid = false;
        }
        return;
    }

//      Name: Validate
//   Purpose: Verify Blank Character Is Not In Input Alphabet And Is In Tape Alphabet
//   
// Operation: 
//            If blank character is in input alphabet the Turing machine is set to an invalid state.
//            If blank character is not in tape alphabet the Turing machine is set to an invalid state.
    void tape::Validate(bool &invalid_Continue)
    {
        if(this->IA->Is_Element(this->blank_Character))
        {
            cout << "Blank Character " << this->blank_Character << " Is In Input Alphabet\n";
            invalid_Continue = true;
        }
        if(!this->TA->Is_Element(this->blank_Character))
        {
            cout << "Blank Character " << this->blank_Character << " Is Not In Tape Alphabet\n";
            invalid_Continue = true;
        }
        return;
    }

//      Name: View 
//   Purpose: Display The Blank Character In A Formal Format 
    void tape::View()
    {
        cout << "B = " << this->blank_Character << "\n";
        return;
    }

//      Name: Initialize
//   Purpose: Setup The Beggining Tape Of The Turing Machine
//
// Operation:
//           This resets the current cell of the turing machine to 0, and the input string to
//           the currently chose input string parameter. If its \ then it is an empty string.
//           Each string is appended with a blank character to signify the end of the tape.
    void tape::Initialize(string input_String)
    {
        if(input_String == "\\") { input_String = ""; }
        this->cells = input_String + this->blank_Character;
        current_Cell = 0;
        return;
    }

//      Name: Update
//   Purpose: Within A Transition This Will Update the Tape
//
// Operation:
//           Using the write character is will set the current cell character to this character. Then the current cell will either be
//           moved left or right depending on "L" or "R" as the direction. If a left move is made when the current cell is at zero
//           the application will crash due to this outcome.
    void tape::Update(char write_Character, direction move_Direction)
    {
        move_Direction = toupper(move_Direction);
        cells[current_Cell] = write_Character;
        if( (move_Direction == 'L') && (this->current_Cell == 0) ) { throw crash("Left Move From First Cell", true); }
        if( (move_Direction == 'R') && (this->current_Cell == (int)cells.size()-1) ){ this->cells += this->blank_Character; } //Crash WIll happen if it enters this if CRASH TYPE [BAD ALLOC]
        if(move_Direction == 'L'){ this->current_Cell--; }else if(move_Direction == 'R'){ this->current_Cell++; }
    }

//      Name: Left
//   Purpose: Displays The Left side of Current cell of the Tape 
//
// Operation:
//            Using the maximum number of cells it will display only that amount of cells.
//            if there are more it will use a '<' to hide the rest of the tape.
    string tape::Left(int maximum_Number_Of_Cells)
    {
        int first_Cell = max(0, this->current_Cell-maximum_Number_Of_Cells);
        string value = this->cells.substr(first_Cell, this->current_Cell-first_Cell); 
        if((int)value.size() < this->current_Cell){ value.insert(0,"<"); } 
        return value;
    }

//      Name: Right
//   Purpose: Displays The Right side with the Current cell of the Tape 
//
// Operation:
//            Using the maximum number of cells it will display only that amount of cells.
//            if there are more it will use a '>' to hide the rest of the tape.         
    string tape::Right(int maximum_Number_Of_Cells)
    {
        int end_Cell = (int)this->cells.size() - 1;
        while( (end_Cell >= this->current_Cell) && (this->cells[end_Cell] == this->blank_Character) ){ end_Cell--; }
        int last_Cell = min(end_Cell, this->current_Cell + (maximum_Number_Of_Cells - 1)); //-1 for index
        string value = this->cells.substr(this->current_Cell, last_Cell - this->current_Cell + 1 ); // + 1 for size
        if((int)value.size() < end_Cell - this->current_Cell + 1 ){ value.append(">"); } // + 1 for size 
        return value;
    }

//      Name: Current_Character
//   Purpose: Returns The Character The Current Cell Points To On The Tape
    char tape::Current_Character()
    { 
        return this->cells[this->current_Cell];
    }

//      Name: Is_First_Cell
//   Purpose: Return True Or False If Current Cell Is At The Beginning Of The Tape
    bool tape::Is_First_Cell()
    {
        return this->current_Cell == 0;
    }