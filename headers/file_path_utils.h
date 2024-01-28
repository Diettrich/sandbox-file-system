//
// Created by Anouar Zougrar on 26/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_FILE_PATH_UTILS_H
#define SANDBOX_FILE_SYSTEM_FILE_PATH_UTILS_H

#include "path.h"
#include "file_node.h"
#include "shell.h"

struct File_node *get_file_node_from_path(struct Path *path, struct Shell *shell);


/**
 * Generates a Path structure from a given File_node.
 * @param struct File_node *file_node
 * @return struct Path *
 *
 * Returns NULL on error.
 */
struct Path *get_path_from_file_node(struct File_node *file_node);

/**
 * Returns the path tokens of the given file node.
 * @param File_node *file_node
 * @return char **
 *
 * Returns a NULL terminated array of strings.
 * Returns NULL on error.
 */
char **get_path_tokens(struct File_node *file_node);

/**
 * Returns the number of path tokens of the given file node.
 * @param File_node *file_node
 * @return int the number of path tokens
 */
int get_path_tokens_count(struct File_node *file_node);


#endif //SANDBOX_FILE_SYSTEM_FILE_PATH_UTILS_H
