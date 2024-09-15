//               Module: input_strings
//                 File: input_strings.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//              This module defines all the methods within the class input string. The methods within
//              this module prepare the input strings from the .str file and sends error if any. Also
//              The input strings are allowed to be modified using these methods as well as saving the
//              strings to a file.
#include "input_strings.h"
#include <vector>
#include <string>
#include <fstream> //fstream (Read and Write) //ifstream (Read) //ofstream (write)
#include <iostream>
using namespace std;

//      Name: inputs_strings
//   Purpose: Initialize Objects Within Class
    input_strings::input_strings(string input_Strings_File_Name)
    {
        this->input_Strings_File_Name = input_Strings_File_Name;
        return;
    }

//      Name: ~inputs_strings
//   Purpose: Release Objects From Memory To Avoid Memory Leaks at exit
    input_strings::~input_strings()
    {
        
    }

//      Name: Load
//   Purpose: Read In The Input Strings from the Input Strings File To Import Into Application
//
// Operation:
//            Reads from the file input strings and reads line by line. If there are any spaces within a input string in the file or
//            the input string is a duplicate in the set/list(vector) it is not included in the input string set(vector) and the file
//            of strings is considered modified within memory.
    void input_strings::Load(ifstream &input_Strings)
    {
        string inputStringTemp;
        bool error = false;
        if(input_Strings.fail()){ return; }
        else
        { 
            while( getline(input_Strings, inputStringTemp) )
            {
                for(long unsigned int i = 0; i < inputStringTemp.size() && !error; i++)
                {
                    if(inputStringTemp[i] == ' ')
                    {
                        error = true;
                    }
                }

                
                if(this->Is_Element(inputStringTemp) || error)
                {
                    this->Set_Input_String_Modified_True();
                    error = false;
                }
                else
                {
                    this->input_Strings.push_back(inputStringTemp);
                }

            }
            input_Strings.close();
            cout << "Input Strings Successfully Loaded\n";
        } 

        return;
    }
 
//      Name: View
//   Purpose: Displays All Input Strings In Memory Otherwise If None Exists Displays Empty
    void input_strings::View()
    {
        cout << "\n";
        cout << "Input Strings: ";
        if(this->input_Strings.size() == 0){ cout << "Empty" << "\n"; }
        else{ cout << "\n"; }
        for(int i = 0; i < (int)this->input_Strings.size(); i++)
        {
            cout << i+1 << ". " << this->input_Strings[i] << "\n";
        }

        return;
    }

//      Name: Get_Input_String
//   Purpose: Returns An Input String Within Set At Position In List(Index == Position - 1)
    string input_strings::Get_Input_String(int input_String_List_Position)
    {
        if(0 < input_String_List_Position && input_String_List_Position <= (int)this->input_Strings.size())
        {
            return this->input_Strings[input_String_List_Position-1];
        }

        return ""; //Possible Fatal Error If Reaches Here // Above if statement avoids seg fault but this return can still create unexpected results // Checks are done in Commands Class
    }

//      Name: Is_Element
//   Purpose: Veify If A String Is Within The Input Strings Set(vector)
//
// Operation:
//            return true if it exists in the set otherwise false.
    bool input_strings::Is_Element(string value)
    {
        for(string value2 : this->input_Strings)
        {
            if(value2 == value)
            {
                return true;
            }
        }
        return false;
    }

//      Name: Insert
//   Purpose: Inserts A String Into The Input Strings Set At Last Postition
    void input_strings::Insert(string user_Input_String)
    {
        this->input_Strings.push_back(user_Input_String);
        return;
    }

//      Name: Delete
//   Purpose: Removes An Existing String In the Input Strings Set At Position Specified(index == position - 1)
    void input_strings::Delete(int User_Input_Position)
    {
        if(0 < User_Input_Position && User_Input_Position <= (int)this->input_Strings.size())
        {
            this->input_Strings.erase(this->input_Strings.begin() + (User_Input_Position-1));
        }
        return;
    }
    
//      Name: Save_Input_Strings
//   Purpose: Saves Inputs Strings Set/List(vector) Into A File With The Object File Name
    void input_strings::Save_Input_Strings()
    {
        if(this->input_String_Modified)
        {
            ofstream input_Strings(this->input_Strings_File_Name);
            if(input_Strings.fail()){ cout << "[Error]: Could Not Write To A File Named " << this->input_Strings_File_Name << " With The Modified Input Strings" << "\n";}
            else
            { 
                for(long unsigned int i = 0; i < this->input_Strings.size(); i++)
                {
                    input_Strings << this->input_Strings[i];

                    if((i+1) < this->input_Strings.size() ){ input_Strings << "\n"; }
                }
                cout << "Successfully Wrote To A File Called " << this->input_Strings_File_Name << " With The Modified Input Strings" << "\n";
            }
        }
        return;
    }

//      Name: Set_Input_String_Modified_True
//   Purpose: Set The Modified Object in this class to True
    void input_strings::Set_Input_String_Modified_True()
    {
        this->input_String_Modified = true;
    }

//      Name: Get_Input_String_Modified_True
//   Purpose: returns The value of the Modified Object in this class
    bool input_strings::Get_Input_String_Modified_True()
    {
        return this->input_String_Modified;
    }

//      Name: Get_Input_String_Size
//   Purpose: Returns the size of the inputs strings set/list(vector) In Memory
    int input_strings::Get_Input_String_Size()
    {
        return this->input_Strings.size();
    }