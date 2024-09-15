//               Module: configuration_settings_header
//                 File: configuration_settings.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module holds the class defintion for the configuation_settings with its objects and methods. 
#ifndef CONFIGURATION_SETTINGS_H
#define CONFIGURATION_SETTINGS_H

class configuration_settings{
private:
    int max_Number_Of_Cells = 32;
    int max_Number_Of_Transitions = 1;
public:
    int Get_Max_Num_Of_Cells();
    int Get_Max_Num_Of_Transitions();
    void Set_Max_Num_Of_Cells(int max_Cells);
    void Set_Max_Num_Of_Transitions(int max_Transitions);
};

#endif