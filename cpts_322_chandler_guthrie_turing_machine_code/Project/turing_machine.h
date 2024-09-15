//               Module: turing_machine_header
//                 File: turing_machine.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module holds the class definition for the turing machine with its objects and methods. 
#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H



#include "turingmachine_parts/tape.h"
#include "turingmachine_parts/tape_alphabet.h"
#include "turingmachine_parts/input_alphabet.h"
#include "turingmachine_parts/states.h"
#include "turingmachine_parts/final_states.h"
#include "turingmachine_parts/transition.h"
#include "turingmachine_parts/transition_function.h"


#include <vector>
#include <string>
using namespace std;

class turing_machine{
private:
    vector<string> description;
    string initial_State;
    string current_State;
    string original_Input_String;
    int total_Number_Of_Transitions = 0;
    bool valid = true;
    bool invalid_Continue = false; 
    bool used = false;
    bool operating = false;
    bool accepted = false;
    bool rejected = false;
    
    tape_alphabet TA;
    input_alphabet IA;
    tape T;
    states S;
    final_states FS;
    transition_function TF;
public:
    turing_machine(string definition_File_Name); 
    ~turing_machine();
    void View_Definition(); 
    void View_Instantaneous_Description(int maximum_Number_Of_Cells); 
    void Initialize(string input_String); 
    void Perform_Transitions(int maximum_Number_Of_Transitions); 
    void Terminate_Operation(); 
    string Input_String(); 
    int Total_Number_Of_Transitions(); 
    bool Is_Valid_Definition(); 
    bool Is_Valid_Input_String(string value);
    bool Is_Used(); 
    bool Is_Operating(); 
    bool Is_Accepted_Input_String(); 
    bool Is_Rejected_Input_String(); 
};


#endif