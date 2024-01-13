//
// Created by Anouar Zougrar on 7/1/2024.
//

#include "commands.h"

const char *exit_command = "exit";

// TODO: add mkdir command
const char *mkdir_command = "mkdir";

char **parse_command_args(char *command_string) {
    char **tokens = malloc(TOKEN_BUFFER_SIZE * sizeof(char *));
    char *single_token = strsep(&command_string, TOKEN_DELIMITERS);
    unsigned short token_position = 0;

    int i = 0;

    // TODO: add reallocation when token_position exceeds TOKEN_BUFFER_SIZE
    while (single_token != NULL && strcmp(single_token, "") != 0) {
        if (token_position == TOKEN_BUFFER_SIZE) {
            printf("token buffer size exceeded\n");
            exit(1);
        }

        tokens[i] = single_token;
        single_token = strsep(&command_string, TOKEN_DELIMITERS);
        i++;
    }

    tokens[i] = NULL;
    return tokens;
}

char **get_command_args(char **tokens) {
    char **args = malloc(TOKEN_BUFFER_SIZE * sizeof(char *));
    unsigned short token_position = 1;

    while (tokens[token_position] != NULL) {
        args[token_position - 1] = tokens[token_position];
        token_position++;
    }

    args[token_position - 1] = NULL;
    return args;
}

enum Command_type parse_command_string(char *command_string) {
    if (strcmp(command_string, exit_command) == 0) {
        return EXIT;
    } else if (strcmp(command_string, mkdir_command) == 0) {
        return MKDIR;
    }

    return UNKNOWN;

}

struct Command parse_string_command(char *command_string) {
    char **tokens = parse_command_args(command_string);
    struct Command command;

    if (tokens[0] == NULL) {
        command.command_type = UNKNOWN;
        command.args = NULL;
        return command;
    }

    command.command_type = parse_command_string(tokens[0]);
    command.args = get_command_args(tokens);

    free(tokens);

    return command;
}
