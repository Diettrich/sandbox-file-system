//
// Created by Anouar Zougrar on 11/1/2024.
//

#include <stdlib.h>

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

int get_children_count(struct File_node *parent) {
    if (parent == NULL) {
        return -1;
    }

    struct File_node *current_child = parent->children;
    unsigned short children_count = 0;

    while (current_child != NULL) {
        current_child = current_child->next;
        children_count++;
    }

    return children_count;
}

struct File_node **get_children_list(struct File_node *parent) {
    if (parent == NULL) {
        return NULL;
    }

    const int children_count = get_children_count(parent);
    struct File_node **children_list = malloc((children_count + 1) * sizeof(struct File_node *));
    struct File_node **children_list_ptr = children_list;
    struct File_node *current_child = parent->children;

    while (current_child != NULL) {
        *children_list_ptr = current_child;
        children_list_ptr++;
        current_child = current_child->next;
    }

    *children_list_ptr = NULL;
    return children_list;
}