//
// Created by Anouar Zougrar on 7/1/2024.
//

#include "commands.h"

const char *exit_command = "exit";
const char *mkdir_command = "mkdir";

short execute_exit_command() {
    return 0;
}

short execute_mkdir_command(struct Command command, struct Shell *shell) {
    if (command.args == NULL || command.args[0] == NULL) {
        printf("mkdir: missing operand\n");
        return 1;
    }

    struct File_node *new_directory = create_file_node(command.args[0], DIRECTORY_TYPE);
    struct File_node *current_directory = shell->current_directory;

    new_directory = append_child(current_directory, new_directory);

    if (new_directory == NULL) {
        printf("mkdir: cannot create directory '%s'\n", command.args[0]);
        return 0;
    }

    return 1;
}



