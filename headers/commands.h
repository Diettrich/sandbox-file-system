//
// Created by Anouar Zougrar on 7/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_COMMANDS_H
#define SANDBOX_FILE_SYSTEM_COMMANDS_H

#include "shell.h"

enum Command_type {
    UNKNOWN,
    EMPTY,
    EXIT,
    MKDIR,
    CD,
    LS,
};

struct Command {
    enum Command_type command_type;
    char **args;
};

extern const char *exit_command;
extern const char *mkdir_command;
extern const char *cd_command;
extern const char *ls_command;

short execute_exit_command();

short execute_mkdir_command(struct Command command, struct Shell *shell);

short execute_cd_command(struct Command command, struct Shell *shell);

short execute_ls_command(struct Command command, struct Shell *shell);

#endif //SANDBOX_FILE_SYSTEM_COMMANDS_H
