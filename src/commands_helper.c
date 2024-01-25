//
// Created by Anouar Zougrar on 13/1/2024.
//

#include "commands_helper.h"
#include "commands.h"

struct Command parse_command(char *command_string) {
    char **tokens = get_line_tokens(command_string);
    struct Command command;

    if (tokens[0] == NULL) {
        command.command_type = EMPTY;
        command.args = NULL;
        return command;
    }

    command.command_type = get_command_type(tokens[0]);
    command.args = get_command_args(tokens);

    free(tokens);

    return command;
}

enum Command_type get_command_type(char *command_string) {
    if (strcmp(command_string, exit_command) == 0) {
        return EXIT;
    } else if (strcmp(command_string, mkdir_command) == 0) {
        return MKDIR;
    } else if (strcmp(command_string, cd_command) == 0) {
        return CD;
    } else if (strcmp(command_string, ls_command) == 0) {
        return LS;
    }

    return UNKNOWN;

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

char **get_line_tokens(char *command_string) {
    char **tokens = malloc(TOKEN_BUFFER_SIZE * sizeof(char *));
    char *single_token = strsep(&command_string, TOKEN_DELIMITERS);
    unsigned short token_position = 0;

    // TODO: add reallocation when token_position exceeds TOKEN_BUFFER_SIZE
    while (single_token != NULL && strcmp(single_token, "") != 0) {
        if (token_position == TOKEN_BUFFER_SIZE) {
            printf("token buffer size exceeded\n");
            exit(1);
        }

        tokens[token_position] = single_token;
        single_token = strsep(&command_string, TOKEN_DELIMITERS);
        token_position++;
    }

    tokens[token_position] = NULL;
    return tokens;
}