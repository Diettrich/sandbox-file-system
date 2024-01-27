//
// Created by Anouar Zougrar on 26/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_UTILS_H
#define SANDBOX_FILE_SYSTEM_UTILS_H

#define MAX_FILE_NAME_LENGTH 255


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

/*
 * @param name: the name to be validated
 *
 * This function validates a file node name.
 * It returns 1 if the name is valid, 0 otherwise.
 *
 * A valid name is a string that contains only:
 * - letters
 * - numbers
 * - underscores
 * - dots
 * - dashes
 */
short validate_file_node_name(char *name);

#endif //SANDBOX_FILE_SYSTEM_UTILS_H
