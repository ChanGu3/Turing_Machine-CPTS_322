//               Module: main
//                 File: main.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This Module is the entry point to the application creating an instance of the class commands
//                 from the Turing machine name the user inputs when running the executable.
#include "commands.h"
#include "input_strings.h"
#include "configuration_settings.h"
#include "turing_machine.h"
#include <iostream>

using namespace std;

//      Name: main
//   Purpose: Execution Entry Point
//
// Operation:
//            The main function is the entry point to this entire application
//            It serves as a way to check for the correct number of terminal arguments.
//            Then it uses the second terminal agrument which is the name of the turing machine
//            and creates the instance of commands using this name as an argument.
int main(int argc, char *argv[])
{
    // Checking For Terminal Arguments Format
    if(argc > 2) { cout << "To Many Arguments Failed Opening Application" << endl; return 0; }
    if(argc < 2) { cout << "Did Not Include Turing Machine Name Failed Opening Application" << endl; return 0; }

    //Create The commandInstance
        // Will Also Create The Following Classes Inside
        //     configuration_settings CS;
        //     input_strings IS;
        //     turing_machine TM;
    string turing_Machine_Name = argv[1];
    commands commandInstance(turing_Machine_Name);
    
    return 0;
}




