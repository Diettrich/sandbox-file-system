//
// Created by Anouar Zougrar on 7/1/2024.
//

#ifndef FILE_SYSTEM__MSIP_COMMANDS_H
#define FILE_SYSTEM__MSIP_COMMANDS_H

#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

enum Command_type {
    UNKNOWN,
    EXIT,
};

struct Command {
    enum Command_type command_type;
    char **args;
};


struct Command parse_string_command(char *command_string);

#endif //FILE_SYSTEM__MSIP_COMMANDS_H
