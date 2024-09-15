//               Module: commands
//                 File: commands.cpp
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
// 
#include "commands.h"
#include "typedef/command_t.h"
#include "typedef/crash.h"
#include "input_strings.h"
#include "configuration_settings.h"
#include "turing_machine.h"

#include <exception>
#include <string>
#include <iostream>


using namespace std;

//      Name: commands
//   Purpose: Create The Configuration Settings Instance, Turing Machine Instance, and Input String Instance. Then Continue Asking For Commands Indefinitely
//
// Operation:
//            If The Turing Machine Created is Invalid it will fail then exit the application peacefully.
//            Otherwise it will continue by displaying a successful Turing Machine then the input strings 
//            will be loaded and if the file exist and its been modified It will display to the user the event.
//            After everything Is loaded properly then it will prompt for a command indefinitely. 
commands::commands(string name_Of_Turing_Machine_P):CS(), //Create Class Instance Of Configuration Settings
                                                    TM(name_Of_Turing_Machine_P + ".def"), //Create Class Instance Of Turing Machine
                                                    IS(name_Of_Turing_Machine_P + ".str")  //Create Class Instance Of Input Strings
{
    this->name_Of_Turing_Machine = name_Of_Turing_Machine_P;

    // Clean Up If Invalid
    if(this->TM.Is_Valid_Definition() == false)
    {
        cout << "Turing Machine Definition Did Not Load Successfully" << "\n"; 
        cout << "Closed Application" << "\n";
        this->TM.~turing_machine();
        this->IS.~input_strings();
        exit(EXIT_SUCCESS);   
    }
    else
    {
        cout << "Turing Machine Definition Successfully Loaded" << "\n";
    }

    //Load Input Strings
    ifstream input_Strings(this->name_Of_Turing_Machine + ".str");
    this->IS.Load(input_Strings);
    //Validate Input String List
    for(int ind = 0; ind < this->IS.Get_Input_String_Size(); ind++)
    {
        if(!this->TM.Is_Valid_Input_String(this->IS.Get_Input_String(ind+1))) 
        {
            this->IS.Set_Input_String_Modified_True();
            this->IS.Delete(ind+1);
            ind--;
        }
    }
    if(this->IS.Get_Input_String_Modified_True())
    {
        cout << "[Error]: Some Input Strings Have Been Removed Due To Them Not Being Valid" << "\n";
        this->IS.Set_Input_String_Modified_True();
    }


    // LOOKING FOR COMMANDS
    string userInput;
    while(true)
    {
        cout << "\n";
        cout << "Command: "; 
        getline(cin, userInput);
        if(userInput.size() == 1)
        {
            User_Command(userInput[0]);
            if(this->userCommand != ERROR){ Activate_Command(); }
            else{ } //ERROR char is not a commmand 
        }
        else if(userInput.size() > 1)
        {  } // SIZE OF INPUT IS TOO LARGE
    }

    return;
}

//      Name: User_Command
//   Purpose: Sets The Object Within This class UserCommand To Its Respective Character From The Parameter 
void commands::User_Command(char user_Input_Command)
{
    switch (tolower(user_Input_Command))
    {
        case 'h': //Help
            this->userCommand = HELP;
            break; 
        case 'e': //Set
            this->userCommand = SET;
            break;
        case 't': //Truncate
            this->userCommand = TRUNCATE;
            break;
        case 'i': //Insert
            this->userCommand = INSERT;
            break;
        case 'd': //Delete
            this->userCommand = DELETE;
            break;
        case 'r': //Run
            this->userCommand = RUN;
            break;
        case 'v': //View
            this->userCommand = VIEW;
            break;
        case 'w': //Show
            this->userCommand = SHOW;
            break;
        case 'l': //List
            this->userCommand = LIST;
            break;
        case 'q': //Quit
            this->userCommand = QUIT;
            break;
        case 'x': //Exit 
            this->userCommand = EXIT;
            break;
        default:
            this->userCommand = ERROR;
            break;
    }
    return;
}

//      Name: Activate_Command
//   Purpose: For A Certain Commmand Input By The User Will Cause An Event To Occur Within The Application 
//
// Operation:
//            For Each Command Within the enum stored values there is a possible event that will display,
//            to the user certain information or it will set/insert/remove objects within other classes to
//            in order to operate the Turing Machine. Help, Set, Truncate, Insert, Delete, Run, View, Show,
//            List, Quit, and Exit are all the possible commands. Help Displays Info About Commands. Set 
//            sets the max transitions. Truncate sets the max visible cells in the tape from left and right. 
//            Insert places new input string into list. Delete removes input string from list. Run operates on
//            the input string provided and transitions everytime run command is entered otherwise it may stop
//            by accepting, rejecting, or crashing input string. View Displays formal definition of turing machine.
//            Show displays an about application with status information about the turing machine. List displays if 
//            any all the input string in the memory. Quit stops the turing machine from running on an input string
//            causing it to not accept or reject the input string. Exit exits the application without any warnings 
//            of the status of the turning machine and saves the input string list if modified. Crashes based on out 
//            of memory will stop execution/application completely.
void commands::Activate_Command()
{

    string userInput;
    int userInputNum;
    int inputNumSize = 0;
    switch (this->userCommand)
    {
        case HELP: //Help
            Help();
            break; 
        case SET: //Set
            cout << "\n";
            cout << "Input Max Transitions (Current " << CS.Get_Max_Num_Of_Transitions() << "): " ;
            getline(cin, userInput);
            try{ userInputNum = stoi(userInput); }
            catch(exception& e){ userInputNum = -1; }
            if(userInputNum != -1){ for(int i = userInputNum; i != 0; i = i/10){ inputNumSize++; }   }
            if( 0 < userInputNum && (int)userInput.size() == inputNumSize) { CS.Set_Max_Num_Of_Transitions(userInputNum); cout << "Successfully Set The Max Transition Size To " << CS.Get_Max_Num_Of_Transitions() << "\n";}
            else if(userInput.size() != 0){ cout << "[Error]: Input Is Not A Positive Number\n"; }
            break;
        case TRUNCATE: //Truncate
            cout << "\n";
            cout << "Input Max Cells For Instantaneous Description (Current " << CS.Get_Max_Num_Of_Cells() << "): ";
            getline(cin, userInput);
            try{ userInputNum = stoi(userInput); }
            catch(exception& e){ userInputNum = -1; }
            if(userInputNum != -1){ for(int i = userInputNum; i != 0; i = i/10){ inputNumSize++; }   }
            if( 0 < userInputNum && (int)userInput.size() == inputNumSize) { CS.Set_Max_Num_Of_Cells(userInputNum); cout << "Successfully Set The Max Cells For The Instantaneous Description To " << CS.Get_Max_Num_Of_Cells() << "\n";}
            else if(userInput.size() != 0){ cout << "[Error]: Input Is Not A Positive Number\n"; }
            break;
        case INSERT: //Insert
            cout << "\n";
            cout << "Enter An Input String That Only Includes Characters From The Input_Alphabet: ";
            getline(cin, userInput);
            if(TM.Is_Valid_Input_String(userInput)) 
            { 
                if(this->IS.Is_Element(userInput))
                {
                    cout << "[Error]: The String You Have Entered Already Exists In The Input_Alphabet\n";
                }
                else
                {
                    IS.Insert(userInput); IS.Set_Input_String_Modified_True(); cout << "Successfully Added " << userInput << " To The Input Strings At Position " << IS.Get_Input_String_Size() << "\n";
                }
            }
            else if(userInput.size() != 0){ cout << "[Error]: The String You Have Entered Does Not Contain Only Characters From The Input_Alphabet\n"; }
            break;
        case DELETE: //Delete
            cout << "\n";
            cout << "Enter A Input String Position Number To Delete Input String: ";
            getline(cin, userInput);
            try{ userInputNum = stoi(userInput); }
            catch(exception& e){ userInputNum = -1; }
            if(userInputNum != -1){ for(int i = userInputNum; i != 0; i = i/10){ inputNumSize++; }   }
            if( 0 < userInputNum && userInputNum <= this->IS.Get_Input_String_Size() && (int)userInput.size() == inputNumSize) { cout << "Successfully Deleted Input String " << IS.Get_Input_String(userInputNum) << " At Position " << userInput << "\n"; IS.Delete(userInputNum); IS.Set_Input_String_Modified_True();}
            else if((userInput.size() != 0) && (this->IS.Get_Input_String_Size() != 0)){ cout << "[Error]: Input Is Not A Positive Number Within The Input String List\n"; }
            else if((userInput.size() != 0)) { cout << "[Error]: The Input String List Is Empty\n"; }
            break;
        case RUN: //Run
        try
        {
            if(this->TM.Is_Operating())
            {
                this->TM.Perform_Transitions(this->CS.Get_Max_Num_Of_Transitions());
                cout << "\n";
                this->TM.View_Instantaneous_Description(this->CS.Get_Max_Num_Of_Cells());

                if(this->TM.Is_Accepted_Input_String())
                {
                    cout << "\n";
                    cout << "Input String " << this->TM.Input_String() << " Accepted in " << this->TM.Total_Number_Of_Transitions() << " Transitions" << "\n";
                }
                else if(this->TM.Is_Rejected_Input_String())
                {
                    cout << "\n";
                    cout << "Input String " << this->TM.Input_String() << " Rejected in " << this->TM.Total_Number_Of_Transitions() << " Transitions" << "\n";
                }
                else if(!this->TM.Is_Operating() && !this->TM.Is_Accepted_Input_String() && !this->TM.Is_Rejected_Input_String())
                {
                    cout << "\n";
                    cout << "Turing Machine Force Stopped By Application On The Input String " << this->TM.Input_String() << "\n"; 
                    cout << "Left Move From First Cell" << "\n";
                    cout << this->TM.Input_String() << " Not Accepted nor Rejected In " << this->TM.Total_Number_Of_Transitions() << " Transition(s)" << "\n"; 
                }

            }
            else
            {
                cout << "\n";
                cout << "Enter A Input String Position To Run A String On The Turing Machine: ";
                getline(cin, userInput);
                try{ userInputNum = stoi(userInput); }
                catch(exception& e){ userInputNum = -1; }
                if(userInputNum != -1){ for(int i = userInputNum; i != 0; i = i/10){ inputNumSize++; }   }
                if( 0 < userInputNum && userInputNum <= IS.Get_Input_String_Size() && (int)userInput.size() == inputNumSize) 
                {
                    this->TM.Initialize(this->IS.Get_Input_String(userInputNum));
                    cout << "\n";
                    this->TM.View_Instantaneous_Description(this->CS.Get_Max_Num_Of_Cells());  


                    this->TM.Perform_Transitions(this->CS.Get_Max_Num_Of_Transitions());
                    if(this->TM.Total_Number_Of_Transitions() != 0) { this->TM.View_Instantaneous_Description(this->CS.Get_Max_Num_Of_Cells()); }

                    if(this->TM.Is_Accepted_Input_String())
                    {
                        cout << "\n";
                        cout << "Input String " << this->TM.Input_String() << " Accepted in " << this->TM.Total_Number_Of_Transitions() << " Transitions" << "\n";
                    }
                    else if(this->TM.Is_Rejected_Input_String())
                    {
                        cout << "\n";
                        cout << "Input String " << this->TM.Input_String() << " Rejected in " << this->TM.Total_Number_Of_Transitions() << " Transitions" << "\n";
                    }
                    else if(!this->TM.Is_Operating() && !this->TM.Is_Accepted_Input_String() && !this->TM.Is_Rejected_Input_String())
                    {
                        cout << "\n";
                        cout << "Turing Machine Force Stopped By Application On The Input String " << this->TM.Input_String() << "\n"; 
                        cout << "Left Move From First Cell" << "\n";
                        cout << this->TM.Input_String() << " Not Accepted nor Rejected In " << this->TM.Total_Number_Of_Transitions() << " Transition(s)" << "\n"; 
                    }

                }
                else if((userInput.size() != 0) && (this->IS.Get_Input_String_Size() != 0)){ cout << "[Error]: Input Is Not A Positive Number Within The Input String List\n"; }
                else if((userInput.size() != 0)) { cout << "[Error]: The Input String List Is Empty\n"; }
            }
        }
        catch(exception& error)
        {
            cout << "\n";
            cout << "[Fatal Error]: \n" << error.what() << "\n";
            this->TM.~turing_machine();
            this->IS.~input_strings();
            exit(EXIT_FAILURE);
        }
            break;
        case VIEW: //View
            this->TM.View_Definition();
            break;
        case SHOW: //Show
            this->Show();
            break;
        case LIST: //List
            this->IS.View();
            break;
        case QUIT: //Quit
            if(this->TM.Is_Operating())
            {
                this->TM.Terminate_Operation();
                cout << "\n";
                cout << "Turing Machine Force Stopped By User On The Input String " << this->TM.Input_String() << "\n"; 
                cout << this->TM.Input_String() << " Not Accepted nor Rejected In " << this->TM.Total_Number_Of_Transitions() << " Transition(s)" << "\n"; 
            }
            else
            {
                cout << "\n";
                cout << "[Error]: The Turing Machine Is Not Currently Running On An Input String" << "\n";
            }
            break;
        case EXIT: //Exit 
            this->TM.~turing_machine();
            Exit_The_Application();
            break;
        default:
            // ERROR THIS SHOULD NOT BE HERE....
            break;
    }
    return;
}

//      Name: Exit_The_Application
//   Purpose: Exits The Application Saving The Input Strings To A .str File If It has Been modified  
void commands::Exit_The_Application()
{
    // SAVE INPUT STRING IF CHANGED IF NOT SUCCESS TELL USER
    cout << "\n";
    cout << "Exiting Application..." << "\n";
    this->IS.Save_Input_Strings();
    this->IS.~input_strings();
    cout << "\n";
    cout << "Application Closed" << "\n";
    exit(EXIT_SUCCESS);
}

//      Name: Help
//   Purpose: Displays To The User All Possible Commands In The Application
void commands::Help()
{
    cout << "\n";
    cout << "[H]ELP" << "      " << "Help User\n"
		 << "S[E]T" << "       " << "Set Maximum Number Of Transitions To Perform\n"
		 << "[T]RUNCATE" << "  " << "Truncate Instantaneous Descriptions\n"
		 << "[I]NSERT" << "    " << "Insert Input String Into List\n"
		 << "[D]ELETE" << "    " << "Delete Input String From List\n"
		 << "[R]UN" << "       " << "Run Turing Machine On Input String\n"
		 << "[V]IEW" << "      " << "View Turing Machine\n"
		 << "SHO[W]" << "      " << "Show Status Of Application\n"
		 << "[L]IST" << "      " << "List Input Srings\n"
		 << "[Q]UIT" << "      " << "Quit Operation Of Turing Machine On Input String\n"
		 << "E[X]IT" << "      " << "Exit Application\n";
}

//      Name: Show
//   Purpose: Displays Information About The Application And Its Current State
void commands::Show()
{
    cout << "\n";

    // Class Info Data
	cout 
        << "Course: " << "       Software Engineering (CPTS_322)\n"
		<< "Semester/Year: " << "Spring 2024\n"
		<< "Instructor: " << "   Neil Corrigan\n"
		<< "Author: " << "       Chandler Guthrie\n"
		<< "Verison: " << "      1.1\n";
    cout << "\n";

    // Turing Machine Name And Status
	cout
		<< "Current Turing Machine Name: " << "                 " << this->name_Of_Turing_Machine << "\n"
		<< "Turing Machine Status: " << "                       ";
	if(!this->TM.Is_Used())
	{
		cout << "Turing Machine Has Not Been Run Yet";
    }
    else if(this->TM.Is_Operating())
    {
		cout << "Turing Machine Is Currently Running";
    }
    else if(this->TM.Is_Used())
    {
	    cout << "Turing Machine Completed Running On An Input String";
	}
	cout << "\n";

    // Configuration Settings
    cout
		<< "Max Turing Machine Transitions: " << "              " << this->CS.Get_Max_Num_Of_Transitions() << "\n"
		<< "Max Turing Machine Instantaneous Description: " << "" << this->CS.Get_Max_Num_Of_Cells() << "\n";
	cout << "\n";

    // Print Status of turing machine
	if (this->TM.Is_Operating())
	{
		cout 
			<< "          " << "Current Input String: " << this->TM.Input_String() << "\n"
			<< "          " << "Total Transitions: " << this->TM.Total_Number_Of_Transitions() << "\n";
	    cout << "\n";
	}
	else if (this->TM.Is_Used())
	{
		cout << "Completed Operation On Input String: " << this->TM.Input_String() << "\n";
		if (this->TM.Is_Accepted_Input_String())
		{
			cout << "Input String Was Accepted By The Turing Machine" << " In " << this->TM.Total_Number_Of_Transitions() << " Transitions" << "\n";
		}
		else if(this->TM.Is_Rejected_Input_String())
		{
			cout << "Input String Was Rejected By The Turing Machine" << " In " << this->TM.Total_Number_Of_Transitions() << " Transitions" << "\n";
		}
        else
        {
            cout << "Input String Was Not Rejected Nor Accepted By The Turing Machine" << " In " << this->TM.Total_Number_Of_Transitions() << " Transitions" << "\n";
        }
		cout << "\n";
	}

    // If Input Strings Modified
    cout << "[Input String Modification Status]" << "\n";
	if (this->IS.Get_Input_String_Modified_True())
	{
        cout << "Input String List Has Been Changed Will Write On Exit" << "\n";
	}
	else
	{
        cout << "Input String List Is Unchanged" << "\n";
	}
}