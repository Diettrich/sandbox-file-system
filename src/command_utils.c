//
// Created by Anouar Zougrar on 27/1/2024.
//

#include <stdio.h>

#include "command_utils.h"
#include "utils.h"
#include "file_node.h"

int validate_mkdir_args(char **args) {
    int args_position = 0;

    while (args[args_position] != NULL) {
        if (!validate_file_node_name(args[args_position])) {
            return 0;
        }
        args_position++;
    }

    return 1;
}

int create_directory(char *directory_name, struct File_node *current_directory) {
    struct File_node *file_node = get_child(current_directory, directory_name);
    if (file_node != NULL) {
        printf("mkdir: cannot create directory '%s': File exists\n", directory_name);
        return 0;
    }

    struct File_node *new_directory = create_file_node(directory_name, DIRECTORY_TYPE);
    if (new_directory == NULL) {
        printf("mkdir: cannot create directory '%s'\n", directory_name);
        return 0;
    }

    new_directory = append_child(current_directory, new_directory);
    if (new_directory == NULL) {
        printf("mkdir: cannot create directory '%s'\n", directory_name);
        return 0;
    }

    return 1;
}
