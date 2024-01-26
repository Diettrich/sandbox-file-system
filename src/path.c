//
// Created by Anouar Zougrar on 25/1/2024.
//

#include <stdlib.h>
#include <string.h>

#include "path.h"
#include "utils.h"

struct Path *create_path(char *path_string) {
    struct Path *path = malloc(sizeof(struct Path));

    char *path_string_copy = malloc(sizeof(char) * strlen(path_string));
    strcpy(path_string_copy, path_string);

    path->string_path = path_string_copy;
    path->is_absolute = (short) (path_string[0] == '/');
    path->path_tokens = get_tokens(path_string, DEFAULT_PATH_SEPARATOR, PATH_TOKENS_MAX_LENGTH);

    return path;
}

void destroy_path(struct Path *path) {
    free(path->path_tokens);
    free(path->string_path);
    free(path);
}
