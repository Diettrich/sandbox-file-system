//
// Created by Anouar Zougrar on 13/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_COMMANDS_HELPER_H
#define SANDBOX_FILE_SYSTEM_COMMANDS_HELPER_H

#define TOKEN_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

#include <stdlib.h>
#include <string.h>

enum Command_type {
    UNKNOWN,
    EMPTY,
    EXIT,
    MKDIR,
};

struct Command {
    enum Command_type command_type;
    char **args;
};


struct Command parse_command(char *command_string);

enum Command_type get_command_type(char *command_string);

char **get_command_args(char **tokens);

char **get_line_tokens(char *command_string);

#endif //SANDBOX_FILE_SYSTEM_COMMANDS_HELPER_H
