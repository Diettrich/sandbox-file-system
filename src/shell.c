//
// Created by Anouar Zougrar on 8/12/2023.
//

#include <printf.h>
#include <stdlib.h>

#include "shell.h"
#include "commands.h"

char *read_line() {
    size_t buffer_size = READLINE_BUF_SIZE;
    char *line = malloc(buffer_size * sizeof(char));
    getline(&line, &buffer_size, stdin);
    return line;
}

short exec_command(enum Command command) {
    switch (command) {
        case EXIT:
            return 0;
        case UNKNOWN:
        default:
            printf("unknown command\n");
            return 1;
    }
}

int run_shell() {
    int status = 0;
    char *command_entry = NULL;

    do {
        // TODO print prompt (current directory) to function
        printf("$ ");
        command_entry = read_line();

        // TODO parse command entry into command and arguments

        // parse command
        enum Command command = parse_command_string(command_entry);
        // TODO parse arguments

        // execute command
        status = exec_command(command);
    } while (status == 1);

    return 0;
}
