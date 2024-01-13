//
// Created by Anouar Zougrar on 8/12/2023.
//
#include <stdlib.h>
#include "shell.h"

int main(int argc, char const *argv[]) {
    struct shell *shell = shell_init();

    return run_shell(shell);
}