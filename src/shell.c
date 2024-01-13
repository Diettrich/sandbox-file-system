//
// Created by Anouar Zougrar on 8/12/2023.
//

#include "shell.h"

char *read_command_line() {
    size_t buffer_size = READLINE_BUF_SIZE;
    char *line = malloc(buffer_size * sizeof(char));
    getline(&line, &buffer_size, stdin);
    return line;
}

short exec_command(struct Command command) {
    switch (command.command_type) {
        case EXIT:
            return 0;
        case MKDIR:
            // TODO: add mkdir command
            printf("mkdir command\n");
            return 1;
        case UNKNOWN:
        default:
            printf("unknown command\n");
            return 1;
    }
}

void print_prompt() {
    // TODO print prompt (current directory) to function
    printf("$ ");
}

int run_shell(struct shell *shell) {
    int status = 0;
    char *command_entry = NULL;

    do {
        print_prompt();
        command_entry = read_command_line();

        struct Command command = parse_string_command(command_entry);

        status = exec_command(command);

        free(command_entry);
        free(command.args);
    } while (status == 1);

    return 0;
}

struct shell *shell_init() {
    struct File_node *root = create_file_node("/", DIRECTORY_TYPE);

    struct shell *shell = malloc(sizeof(struct shell));
    shell->root = root;
    shell->current_directory = root;

    return shell;
}
