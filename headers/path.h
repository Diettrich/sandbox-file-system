//
// Created by Anouar Zougrar on 25/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_PATH_H
#define SANDBOX_FILE_SYSTEM_PATH_H

#define PATH_TOKENS_MAX_LENGTH 64
#define DEFAULT_PATH_SEPARATOR "/"

struct Path {
    short is_absolute;
    char *string_path;
    char **path_tokens;
};

struct Path *create_path(char *path_string);

void destroy_path(struct Path *path);

#endif //SANDBOX_FILE_SYSTEM_PATH_H
