//
// Created by Anouar Zougrar on 7/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_COMMANDS_H
#define SANDBOX_FILE_SYSTEM_COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

enum Command_type {
    UNKNOWN,
    EXIT,
    MKDIR,
};

struct Command {
    enum Command_type command_type;
    char **args;
};


struct Command parse_string_command(char *command_string);

#endif //SANDBOX_FILE_SYSTEM_COMMANDS_H