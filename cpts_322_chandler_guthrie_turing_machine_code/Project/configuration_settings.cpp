//               Module: configuration_settings
//                 File: configuration_settings.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//              This module defines all the methods within the class configuration settings. The methods within
//              the module only set and get the objects within its class. So that The turing machine can use them.
#include "configuration_settings.h"

//      Name: Get_Max_Num_Of_Cells
//   Purpose: Returns The Max Number Of Cells Object
    int configuration_settings::Get_Max_Num_Of_Cells()
    {
        return this->max_Number_Of_Cells;
    }

//      Name: Get_Max_Num_Of_Transitions
//   Purpose: Returns The Max Number Of Tranisitions Object    
    int configuration_settings::Get_Max_Num_Of_Transitions()
    {
        return this->max_Number_Of_Transitions;
    }

//      Name: Set_Max_Num_Of_Cells
//   Purpose: Sets The Max Number Of Cells Object by the parameter
    void configuration_settings::Set_Max_Num_Of_Cells(int max_Cells)
    {
        this->max_Number_Of_Cells = max_Cells;
        return;
    }

//      Name: Set_Max_Num_Of_Transitions
//   Purpose: Sets The Max Number Of Tranisitions Object by the parameter
    void configuration_settings::Set_Max_Num_Of_Transitions(int max_Transitions)
    {
        this->max_Number_Of_Transitions = max_Transitions;
        return;
    }