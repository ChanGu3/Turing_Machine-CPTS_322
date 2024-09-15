//               Module: commands_header
//                 File: commands.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module holds the class definition for the commands with its objects and methods. 
#ifndef COMMANDS_H
#define COMMANDS_H

#include "typedef/command_t.h"
#include "input_strings.h"
#include "configuration_settings.h"
#include "turing_machine.h"
#include <string>
#include <iostream>

using namespace std;

class commands {
private:
    command_list userCommand;
    string name_Of_Turing_Machine;

    configuration_settings CS;
    turing_machine TM;
    input_strings IS;
public: 
    commands(string name_Of_Turing_Machine_P);
    void User_Command(char user_Input_Command);
    void Activate_Command();
    void Exit_The_Application();
    void Help();
    void Show();
};

#endif