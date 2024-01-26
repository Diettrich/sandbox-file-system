//
// Created by Anouar Zougrar on 26/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_FILE_PATH_UTILS_H
#define SANDBOX_FILE_SYSTEM_FILE_PATH_UTILS_H

#include "path.h"
#include "file_node.h"
#include "shell.h"

struct File_node *get_file_node_from_path(struct Path *path, struct Shell *shell);

struct Path *get_path_from_file_node(struct File_node *file_node);

#endif //SANDBOX_FILE_SYSTEM_FILE_PATH_UTILS_H
