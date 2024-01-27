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

short validate_file_node_name(char *name) {
    const size_t name_length = strlen(name);
    if (name_length > MAX_FILE_NAME_LENGTH) {
        printf("FILE NAME ERROR: file name exceeds maximum length\n");
        return 0;
    }

    for (int i = 0; i < name_length; ++i) {
        const char current_char = name[i];
        short is_numeric = (short) (current_char >= (signed char) 0x30 && current_char <= (signed char) 0x39);
        short is_uppercase_letter = (short) (current_char >= (signed char) 0x41 && current_char <= (signed char) 0x5A);
        short is_lowercase_letter = (short) (current_char >= (signed char) 0x61 && current_char <= (signed char) 0x7A);
        short is_allowed_special_char = (short) (current_char == (signed char) 0x2E ||
                                                 current_char == (signed char) 0x5F ||
                                                 current_char == (signed char) 0x2D);
        if (!(is_numeric || is_uppercase_letter || is_lowercase_letter || is_allowed_special_char)) {
            printf("FILE NAME ERROR: file name contains invalid characters\n");
            return 0;
        }
    }

    return 1;
}
