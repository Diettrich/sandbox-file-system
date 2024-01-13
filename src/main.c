//
// Created by Anouar Zougrar on 8/12/2023.
//
#include <stdlib.h>
#include "shell.h"

int main(int argc, char const *argv[]) {
    struct Shell *shell = shell_init();

    return run_shell(shell);
}