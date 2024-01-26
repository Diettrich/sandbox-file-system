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
    PWD,
};

struct Command {
    enum Command_type command_type;
    char **args;
};

extern const char *exit_command;
extern const char *mkdir_command;
extern const char *cd_command;
extern const char *ls_command;
extern const char *pwd_command;

short execute_exit_command();

short execute_mkdir_command(struct Command command, struct Shell *shell);

short execute_cd_command(struct Command command, struct Shell *shell);

short execute_ls_command(struct Command command, struct Shell *shell);

short execute_pwd_command(struct Command command, struct Shell *shell);

// debug function
void print_fs_tree(struct File_node *root, int depth);

#endif //SANDBOX_FILE_SYSTEM_COMMANDS_H
