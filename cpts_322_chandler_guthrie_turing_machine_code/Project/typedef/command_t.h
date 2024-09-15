//               Module: command_t
//                 File: command_t.h
//          Application: Interactive Turing Machine
// Programming Language: C++
//             Computer: Lenovo Legion S7 15ACH6
//     Operating System: Windows 11 Home
//               Course: (CPTS_322) Software Engineering I
//               Author: Chandler Guthrie
//                 Date: 4-25-24
// Description:
//             This module holds all the possible commands in an enum starting with an error command
//             that is not apart of the actual commands list but used for error checking.

#ifndef COMMAND_T_H
#define COMMAND_T_H

enum command_list {
    ERROR,
    HELP,
    SET,
    TRUNCATE,
    INSERT,
    DELETE,
    RUN,
    VIEW,
    SHOW,
    LIST,
    QUIT,
    EXIT
};

#endif