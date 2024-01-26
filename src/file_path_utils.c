//
// Created by Anouar Zougrar on 26/1/2024.
//

#include <stdlib.h>
#include <string.h>
#include <printf.h>

#include "file_path_utils.h"
#include "utils.h"

struct File_node *get_file_node_from_path(struct Path *path, struct Shell *shell) {
    struct File_node *current_directory;

    if (path->is_absolute) current_directory = shell->root_directory;
    else current_directory = shell->current_directory;

    int path_token_position = 0;

    while (path->path_tokens[path_token_position] != NULL) {
        if (strcmp(path->path_tokens[path_token_position], ".") == 0) {
            path_token_position++;
            continue;
        }

        if (strcmp(path->path_tokens[path_token_position], "..") == 0) {
            if (current_directory->parent != NULL) {
                current_directory = current_directory->parent;
            }
            path_token_position++;
            continue;
        }
        struct File_node *child = get_child(current_directory, path->path_tokens[path_token_position]);

        if (child == NULL) return NULL;

        current_directory = child;
        path_token_position++;
    }


    return current_directory;
}

struct Path *get_path_from_file_node(struct File_node *file_node) {
    int path_tokens_count = 0;

    struct File_node *current_node = file_node;

    while (current_node != NULL) {
        path_tokens_count++;
        current_node = current_node->parent;
    }

    char **path_tokens = malloc(sizeof(char *) * path_tokens_count);

    current_node = file_node;

    int path_token_position = path_tokens_count - 1;

    while (current_node != NULL) {
        path_tokens[path_token_position] = current_node->file_data->name;
        path_token_position--;
        current_node = current_node->parent;
    }

    char *path_string = join_tokens(path_tokens + 1, DEFAULT_PATH_SEPARATOR);

    char *absolute_path_string = malloc(sizeof(char) * (strlen(path_string) + 1));
    strcpy(absolute_path_string, DEFAULT_PATH_SEPARATOR);
    strcat(absolute_path_string, path_string);

    struct Path *path = create_path(absolute_path_string);

    free(path_tokens);

    return path;
}
