//
// Created by Anouar Zougrar on 7/1/2024.
//


#include <stdio.h>
#include <stdlib.h>

#include "commands.h"

const char *exit_command = "exit";
const char *mkdir_command = "mkdir";
const char *cd_command = "cd";
const char *ls_command = "ls";

short execute_exit_command() {
    return 0;
}

short execute_mkdir_command(struct Command command, struct Shell *shell) {
    if (command.args == NULL || command.args[0] == NULL) {
        printf("mkdir: missing operand\n");
        return 1;
    }

    // TODO: handle mkdir options (e.g. -p)

    int args_position = 0;

    while (command.args[args_position] != NULL) {
        struct File_node *new_directory = create_file_node(command.args[args_position], DIRECTORY_TYPE);
        struct File_node *current_directory = shell->current_directory;

        new_directory = append_child(current_directory, new_directory);

        if (new_directory == NULL) {
            printf("mkdir: cannot create directory '%s'\n", command.args[args_position]);
            return 0;
        }

        args_position++;
    }

    return 1;
}

short execute_cd_command(struct Command command, struct Shell *shell) {
    struct File_node *current_directory = shell->current_directory;

    return 0;
}

short execute_ls_command(struct Command command, struct Shell *shell) {
    // TODO: handle ls args

    if (command.args != NULL && command.args[0] != NULL) {
        printf("ls: too many arguments\n");
        return 1;
    }


    struct File_node *current_directory = shell->current_directory;
    struct File_node **children = get_children_list(current_directory);

    if (children == NULL) {
        return 0;
    }

    for (int i = 0; children[i] != NULL; i++) {
        printf("%s\n", children[i]->file_data->name);
    }

    free(children);

    return 1;
}



