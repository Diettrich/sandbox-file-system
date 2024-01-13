//
// Created by Anouar Zougrar on 11/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_FILE_NODE_H
#define SANDBOX_FILE_SYSTEM_FILE_NODE_H

#include <stdlib.h>

enum File_type {
    FILE_TYPE,
    DIRECTORY_TYPE,
};

struct File_data {
    char *name;
};

struct File_node {
    enum File_type file_type;
    struct File_data *file_data;
    struct File_node *parent;
    struct File_node *children;
    struct File_node *next;
    struct File_node *previous;
};

/* Creates a new Node containing the given data */
/** Returns NULL on error **/
struct File_node *create_file_node(char *name, enum File_type file_type);

/* Inserts a Node as the first child of the given parent */
/** Returns NULL on error **/
struct File_node *prepend_child(struct File_node *parent, struct File_node *child);

/* Inserts a Node as the last child of the given parent */
/** Returns NULL on error **/
struct File_node *append_child(struct File_node *parent, struct File_node *child);

/* Removes a Node */
/** Returns NULL on error **/
struct File_node *remove_node(struct File_node *node);


#endif //SANDBOX_FILE_SYSTEM_FILE_NODE_H
