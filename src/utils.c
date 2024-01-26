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
    while (single_token != NULL && strcmp(single_token, "") != 0) {
        if (token_position == buffer_size) {
            printf("TOKENIZER ERROR: buffer size exceeded\n");
            exit(1);
        }

        tokens[token_position] = single_token;
        single_token = strsep(&string, delimiters);
        token_position++;
    }

    tokens[token_position] = NULL;
    return tokens;
}
