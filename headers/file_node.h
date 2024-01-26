//
// Created by Anouar Zougrar on 11/1/2024.
//

#ifndef SANDBOX_FILE_SYSTEM_FILE_NODE_H
#define SANDBOX_FILE_SYSTEM_FILE_NODE_H

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

/* Returns the children of the given Node */
/** Returns NULL on error **/
struct File_node **get_children_list(struct File_node *parent);

/* Returns the number of children of the given Node */
/** Returns -1 on error **/
int get_children_count(struct File_node *parent);

/* Returns the child of the given Node with the given name */
/** Returns NULL on error **/
struct File_node *get_child(struct File_node *parent, char *child_name);


#endif //SANDBOX_FILE_SYSTEM_FILE_NODE_H
