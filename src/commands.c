//
// Created by Anouar Zougrar on 7/1/2024.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "path.h"
#include "file_path_utils.h"
#include "command_utils.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantFunctionResult"

const char *exit_command = "exit";
const char *mkdir_command = "mkdir";
const char *cd_command = "cd";
const char *ls_command = "ls";
const char *pwd_command = "pwd";

short execute_exit_command() {
    return 0;
}

short execute_mkdir_command(struct Command command, struct Shell *shell) {
    if (command.args == NULL || command.args[0] == NULL) {
        printf("mkdir: missing operand\n");
        return 1;
    }

    if (!validate_mkdir_args(command.args)) {
        return 1;
    }

    int args_position = 0;

    while (command.args[args_position] != NULL) {
        create_directory(command.args[args_position], shell->current_directory);
        args_position++;
    }

    return 1;
}

short execute_cd_command(struct Command command, struct Shell *shell) {
    if (command.args == NULL || command.args[0] == NULL) {
        printf("cd: missing operand\n");
        return 1;
    }

    if (command.args[1] != NULL) {
        printf("cd: too many arguments\n");
        return 1;
    }

    char *arg = malloc(sizeof(char) * strlen(command.args[0]));
    strcpy(arg, command.args[0]);

    struct Path *path = create_path(arg);

    struct File_node *file_node = get_file_node_from_path(path, shell);

    destroy_path(path);

    if (file_node == NULL) {
        printf("cd: no such file or directory: %s\n", command.args[0]);
        return 1;
    }

    shell->current_directory = file_node;

    return 1;
}

short execute_ls_command(struct Command command, struct Shell *shell) {
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

short execute_pwd_command(struct Command command, struct Shell *shell) {
    if (command.args != NULL && command.args[0] != NULL) {
        printf("pwd: too many arguments\n");
        return 1;
    }

    struct Path *path = get_path_from_file_node(shell->current_directory);

    if (path == NULL) {
        printf("pwd: error while getting path\n");
        return 0;
    }

    printf("%s\n", path->string_path);

    destroy_path(path);
    return 1;
}

// debug function
void print_fs_tree(struct File_node *root, int depth) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    printf("%s\n", root->file_data->name);

    struct File_node **children = get_children_list(root);

    for (int i = 0; children[i] != NULL; i++) {
        print_fs_tree(children[i], depth + 1);
    }

    free(children);
}


#pragma clang diagnostic pop