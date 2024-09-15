//               Module: input_strings_header
//                 File: input_strings.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module holds the class definition for the inputs_strings with its objects and methods. 
#ifndef INPUT_STRINGS_H
#define INPUT_STRINGS_H

#include <vector>
#include <string>
#include <fstream> //fstream (Read and Write) //ifstream (Read) //ofstream (write)
#include <iostream>
using namespace std;

class input_strings{
private:
    string input_Strings_File_Name;
    vector<string> input_Strings;
    bool input_String_Modified = false;
public:
    input_strings(string input_Strings_File_Name);
    ~input_strings();
    void Load(ifstream &input_Strings);
    void View();
    string Get_Input_String(int input_String_List_Position);
    void Insert(string user_Input_String);
    void Delete(int User_Input_Position);
    void Save_Input_Strings();
    void Set_Input_String_Modified_True();
    bool Get_Input_String_Modified_True();
    bool Is_Element(string value);
    int Get_Input_String_Size();
};

#endif