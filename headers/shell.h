//
// Created by Anouar Zougrar on 8/12/2023.
//

#ifndef SHELL_H
#define SHELL_H

#include "file_node.h"

#define READLINE_BUF_SIZE 1024

struct Shell {
    struct File_node *root_directory;
    struct File_node *current_directory;

};

struct Shell *shell_init();

int run_shell(struct Shell *shell);

#endif //SHELL_H
