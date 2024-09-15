//               Module: turing_machine
//                 File: turing_machine.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This Module deals with The entirety of the Turing Machine and all its parts that includes Tape Alphabet, Input Alphabet, Tape, States, Final States,
//             and Transition Functions(which also uses transitions). Using All of these classes these methods can preform operations on an input string, display
//             info to the user, and set objects within this class and others to correctly set the states within the turing machien and values for operation.
#include "turing_machine.h"

#include "typedef/uppercase.h"
#include "typedef/crash.h"
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

//      Name: turing_machine
//   Purpose: Initialize Objects Within Class
    turing_machine::turing_machine(string definition_File_Name): TA(), IA(&this->TA), T(&this->IA, &this->TA), S(), FS(&this->S), TF(&this->TA, &this->S, &this->FS)
    {
        ifstream definition(definition_File_Name);
        if(definition.fail()) { cout << "The File Name Is Case Sensitive Make Sure The Entered Turing Machine Name Matches The File Name With The Extension .def" << "\n"; this->valid = false; } 
        

        string value;
        //START Load Description
        if(valid == true)
        {
            /*
            bool isDoneDesc = false;
            int add = 0;
            this->description.push_back("");
            while(!isDoneDesc)
            {
                if( !(definition >> value) )
                {
                    cout << "Missing Keyword After Definition.\n";
                    valid = false;
                    isDoneDesc = true;
                }
                else if((Uppercase(value) == "STATES:")){ isDoneDesc = true; }
                else
                {
                    if(add == 10){ add = 0; this->description.push_back("");}
                    this->description[this->description.size()-1] += value;
                    this->description[this->description.size()-1] += " ";
                    add++;
                }
            }
            */

            string tempLine = "";
            string LineInsert = "";
            int wordLen = 0;

            bool keywordFound = false;
            int length = 0;
            do
            {
                wordLen = 0;
                length = definition.tellg();

                if(getline(definition, tempLine))
                {
                    for(long unsigned int ind = 0; ind < tempLine.size() && !keywordFound; ind++)
                    {
                        value = "";
                        while(tempLine[ind] != ' ' && tempLine[ind] != '\n' && tempLine[ind] != '\0')
                        {
                            value.push_back(tempLine[ind]);
                            ind++;   
                            wordLen++;
                        }

                        if((Uppercase(value) == "STATES:"))
                        {
                            definition.seekg(length+wordLen, ios::beg);
                            keywordFound = true;
                        }
                        else
                        {
                            LineInsert.append(value);
                            if((ind+1) < tempLine.size()){ LineInsert.append(" "); }
                            wordLen++;
                        }
                    }

                    if(LineInsert.size() != 0){ this->description.push_back(LineInsert); }
                    if(tempLine.size() == 0){ this->description.push_back(LineInsert); }
                    LineInsert = "";

                }
                else
                {
                    cout << "Missing Keyword After Definition.\n";
                    valid = false;
                    keywordFound = true; //not really true just so it exits the loop
                }

            }while(!keywordFound);

        }



        //END Load Description
        if(this->valid == true) { this->S.Load(definition, this->valid, this->invalid_Continue); }
            
        if(this->valid == true) { this->IA.Load(definition, this->valid, this->invalid_Continue); }

        if(this->valid == true) { this->TA.Load(definition, this->valid, this->invalid_Continue); }

        if(this->valid == true) { this->IA.Validate(this->invalid_Continue); }

        if(this->valid == true) { this->TF.Load(definition, this->valid, this->invalid_Continue); }

        if(this->valid == true) { this->TF.Validate(this->invalid_Continue); }
        //START Load Initial_State
        if(this->valid == true)
        {
            if( definition >> value )
            {   
                for(int ind = 0; ind < (int)value.size(); ind++)
                {
                    if( (value[ind] != '\\') &&
                        (value[ind] != '[') && (value[ind] != ']')    &&
                        (value[ind] != '<') && (value[ind] != '>')    &&
                        (value[ind] >= '!') && (value[ind] <= '~')
                      )
                    {
                        if(ind < (int)value.size())
                        {
                            this->initial_State = value;
                        }
                    }
                    else
                    {
                        cout << "Illegal Character In Initial State " << value << "\n";
                        this->invalid_Continue = false; 
                    }
                }
            }
                
            if( !(definition >> value) || Uppercase(value) != "BLANK_CHARACTER:" )  
            {
                cout << "Missing Keyword After Initial State.\n";
                valid = false;
            }
        }
        
        //END Load Initial_State
        if(this->valid == true) { this->T.Load(definition, this->valid, this->invalid_Continue); }
        
        if(this->valid == true) { this->T.Validate(this->invalid_Continue); }

        if(this->valid == true) { this->FS.Load(definition, this->valid, this->invalid_Continue); }

        if(this->valid == true) { this->FS.Validate(this->invalid_Continue); }

        if(this->invalid_Continue) { this->valid = false; }

        return;
    }

 //      Name: ~turing_machine
//   Purpose: Release Objects From Memory To Avoid Memory Leaks at exit
    turing_machine::~turing_machine()
    {
        
    }

//      Name: View_Definition
//   Purpose: Displays A Full Formal Description Of The Current Turing Machine Definition
    void turing_machine::View_Definition()
    {

        cout <<  "\n";

        for(string value: this->description){cout << value << "\n";} //Description
        cout << "\n"; //WhiteSpace

        cout << "M = (Q, sigma, gamma, delta, q0, B, F)" << "\n"; //TM 
        cout << "\n"; //WhiteSpace

        this->S.View(); //Print Out States
        cout << "\n"; //WhiteSpace
    
        this->IA.View(); //Print Out Input Alphabet
        cout << "\n"; //WhiteSpace

        this->TA.View(); //Print Out Tape Alphabet
        cout << "\n"; //WhiteSpace

        this->TF.View(); //Print Out Transistion Functions
        cout << "\n"; //WhiteSpace

        cout << "q0 = " << this->initial_State << "\n"; //Print Out Initial State
        cout << "\n"; //WhiteSpace
        
        this->T.View(); //Print Out Blank Character
        cout << "\n"; //WhiteSpace

        this->FS.View(); //Print Out Final State
        
        
        return;
  
    } 

//      Name: View_Instantaneous_Description
//   Purpose: Displays The Tape Of the Turing Machine At The Time Of Call
    void turing_machine::View_Instantaneous_Description(int maximum_Number_Of_Cells) 
    {
        cout << this->Total_Number_Of_Transitions() << ". " << this->T.Left(maximum_Number_Of_Cells) << "[" << this->current_State << "]" << this->T.Right(maximum_Number_Of_Cells) << "\n"; 
        return;
    }

//      Name: Initialize
//   Purpose: Upon Start Of Running On Input Strings it sets Objects Within The Tape and This class
    void turing_machine::Initialize(string input_String)
    {
        this->T.Initialize(input_String);
        current_State = this->initial_State;
        this->total_Number_Of_Transitions = 0;
        this->original_Input_String = input_String;
        this->operating = true;
        this->used = true;
        this->rejected = false;
        this->accepted = false;
        return;
    }

//      Name: Perform_Transitions
//   Purpose: Update Objects Within Class And The Tape Class And Stop Running If Accepted Or Rejected
//
// Operation:
//            If A transition is not found the input string is rejected and if it does it continues transitions by updating specific objects.
//            If the transition is accepted it is because a final state has been reached. 
//            
    void turing_machine::Perform_Transitions(int maximum_Number_Of_Transitions)
    {
        try
        {
            string destination_State; 
            char write_Character;
            direction move_Direction;
            bool found = false;

            for(int i = 0; i < maximum_Number_Of_Transitions; i++)
            {
                this->TF.Find_Transition(this->current_State,this->T.Current_Character(),destination_State,write_Character,move_Direction,found);
                if(found)
                {
                    this->total_Number_Of_Transitions++;
                    this->current_State = destination_State;
                    this->T.Update(write_Character, move_Direction);
                    if(this->FS.Is_Element(this->current_State))
                    {
                        this->accepted = true;
                        this->operating = false;
                        this->used = true; 
                        return;
                    }
                }
                else
                {
                    this->rejected = true;   
                    this->operating = false;
                    this->used = true; 
                    return;
                }
            }
        }
        catch(crash& error)
        {
            this->operating = false;
            this->used = true; 
        }
        
        return;
    }

//      Name: Terminate_Operation
//   Purpose: Quit Running The Turing Machine On An Input String
    void turing_machine::Terminate_Operation()
    {
        this->operating = false;
        this->used = true;     
        return;
    } 

//      Name: Input_String
//   Purpose: Returns The Current/Previous Input String That Was(or is) Running On The Turing Machine 
    string turing_machine::Input_String()
    {
        return this->original_Input_String;
    }

//      Name: Total_Number_Of_Transitions
//   Purpose: Returns The Current Total Number Of Transitions During(or after) Running The Turing Machine 
    int turing_machine::Total_Number_Of_Transitions()
    {
        return this->total_Number_Of_Transitions;
    } 

//      Name: Is_Valid_Definition
//   Purpose: Return If The Defintion File is invalid or not
    bool turing_machine::Is_Valid_Definition() 
    {
        return this->valid;
    }

//      Name: Is_Valid_Input_String
//   Purpose: Returns If the Input String Contains Characters Within the Input Alphabet
//
// Operation:
//            this method goes through the entire string in the parameters'(value) characters and checks if it is an element 
//            of input alphabet if any character is not in the input alphabet this will return false. Otherwise if each character
//            is an element is passes returning true. 
    bool turing_machine::Is_Valid_Input_String(string value)
    {
        if(value == "" || value.size() == 0){ return false; } //empty(no characters)
        
        for(char valueC: value)
        {
            if(valueC == '\\' && value.size() == 1)
            {
                return true;
            }

            if(!this->IA.Is_Element(valueC))
            {
                return false;
            }
        }

        return true;
    }

//      Name: Is_Used
//   Purpose: Returns The Object Of This Class used
    bool turing_machine::Is_Used()
    {

        return this->used;
    }

//      Name: Is_Operating
//   Purpose: Returns The Object Of This Class operating
    bool turing_machine::Is_Operating()
    {
        return this->operating;
    }

//      Name: Is_Accepted_Input_String
//   Purpose: Returns The Object Of This Class accepted
    bool turing_machine::Is_Accepted_Input_String()
    {

        return this->accepted;
    }

//      Name: Is_Rejected_Input_String
//   Purpose: Returns The Object Of This Class rejected
    bool turing_machine::Is_Rejected_Input_String()
    {

        return this->rejected;
    } 