//
// Created by Anouar Zougrar on 26/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_UTILS_H
#define SANDBOX_FILE_SYSTEM_UTILS_H


/*
 * @param string: the string to be split into tokens, it is modified
 * @param delimiters: the delimiters used to split the string
 * @param buffer_size: the maximum number of tokens
 *
 * This function takes a string and a delimiter and returns an array of tokens.
 * The tokens are separated by the delimiter.
 * The last element of the array is NULL.
 * The array is allocated in the heap.
 * The caller is responsible for freeing the memory.
 */
char **get_tokens(char *string, char *delimiters, unsigned short buffer_size);

char *join_tokens(char **tokens, char *separator);

#endif //SANDBOX_FILE_SYSTEM_UTILS_H
