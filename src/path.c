//
// Created by Anouar Zougrar on 25/1/2024.
//

#include <stdlib.h>
#include <string.h>

#include "path.h"
#include "utils.h"

struct Path *create_path(char *path_string) {
    struct Path *path = malloc(sizeof(struct Path));
    path->string_path = malloc(strlen(path_string) + 1);
    strcpy(path->string_path, path_string);
    path->is_absolute = (short) (path_string[0] == '/');
    path->path_tokens = get_tokens(path_string, DEFAULT_PATH_SEPARATOR, PATH_TOKENS_MAX_LENGTH);

    return path;
}

void destroy_path(struct Path *path) {
    free(path->string_path);
    free(path->path_tokens);
    free(path);
}