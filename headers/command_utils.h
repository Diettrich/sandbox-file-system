//
// Created by Anouar Zougrar on 27/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_COMMAND_UTILS_H
#define SANDBOX_FILE_SYSTEM_COMMAND_UTILS_H

#include "shell.h"

/**
 * Validates the arguments of the mkdir command
 * @param char **args the arguments of the mkdir command
 * @return 1 if the arguments are valid, 0 otherwise
 */
int validate_mkdir_args(char **args);

/**
 * Creates a directory with the given name in the current directory
 * @param char *directory_name the name of the directory to create
 * @param struct File_node *current_directory the current directory
 * @return 1 if the directory was created successfully, 0 otherwise
 */
int create_directory(char *directory_name, struct File_node *current_directory);


#endif //SANDBOX_FILE_SYSTEM_COMMAND_UTILS_H
