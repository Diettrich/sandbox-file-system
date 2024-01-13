//
// Created by Anouar Zougrar on 11/1/2024.
//

#include "file_node.h"

struct File_node *create_file_node(char *name, enum File_type file_type) {
    struct File_node *file_node = malloc(sizeof(struct File_node));
    struct File_data *file_data = malloc(sizeof(struct File_data));

    file_data->name = name;
    file_node->file_data = file_data;
    file_node->file_type = file_type;
    file_node->parent = NULL;
    file_node->children = NULL;
    file_node->next = NULL;
    file_node->previous = NULL;

    return file_node;
}

struct File_node *prepend_child(struct File_node *parent, struct File_node *child) {
    if (parent == NULL || child == NULL) {
        return NULL;
    }

    if (parent->children == NULL) {
        parent->children = child;
        child->parent = parent;
        return child;
    }

    struct File_node *first_child = parent->children;
    first_child->previous = child;
    child->next = first_child;
    child->parent = parent;
    parent->children = child;

    return child;
}

struct File_node *append_child(struct File_node *parent, struct File_node *child) {
    if (parent == NULL || child == NULL) {
        return NULL;
    }

    if (parent->children == NULL) {
        parent->children = child;
        child->parent = parent;
        return child;
    }

    struct File_node *last_child = parent->children;
    while (last_child->next != NULL) {
        last_child = last_child->next;
    }

    last_child->next = child;
    child->previous = last_child;
    child->parent = parent;

    return child;
}
