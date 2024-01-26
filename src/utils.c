//
// Created by Anouar Zougrar on 26/1/2024.
//

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include "utils.h"

char **get_tokens(char *string, char *delimiters, unsigned short buffer_size) {
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *single_token = strsep(&string, delimiters);
    unsigned short token_position = 0;

    // TODO: add reallocation when token_position exceeds TOKEN_BUFFER_SIZE
    while (single_token != NULL) {
        if (token_position == buffer_size) {
            printf("TOKENIZER ERROR: buffer size exceeded\n");
            exit(1);
        }

        if (strcmp(single_token, "") != 0) {
            tokens[token_position] = single_token;
            token_position++;
        }

        single_token = strsep(&string, delimiters);
    }

    tokens[token_position] = NULL;
    return tokens;
}

char *join_tokens(char **tokens, char *separator) {
    int tokens_count = 0;
    int char_count = 0;

    while (tokens[tokens_count] != NULL) {
        char_count += (int) strlen(tokens[tokens_count]);
        tokens_count++;
    }

    char_count += (int) strlen(separator) * (tokens_count - 1);
    char *joined_string = malloc(sizeof(char) * char_count);

    for (int i = 0; i < tokens_count; i++) {
        strcat(joined_string, tokens[i]);
        if (i != tokens_count - 1) strcat(joined_string, separator);
    }

    return joined_string;
}
