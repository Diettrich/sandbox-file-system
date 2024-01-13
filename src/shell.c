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

short exec_command(struct Command command, struct Shell *shell) {
    switch (command.command_type) {
        case EXIT:
            return execute_exit_command();
        case MKDIR:
            return execute_mkdir_command(command, shell);
        case EMPTY:
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

int run_shell(struct Shell *shell) {
    int status = 0;
    char *command_entry = NULL;

    do {
        print_prompt();
        command_entry = read_command_line();

        struct Command command = parse_command(command_entry);

        status = exec_command(command, shell);

        free(command_entry);
        free(command.args);
    } while (status == 1);

    return 0;
}

struct Shell *shell_init() {
    struct File_node *root = create_file_node("/", DIRECTORY_TYPE);

    struct Shell *shell = malloc(sizeof(struct Shell));
    shell->root = root;
    shell->current_directory = root;

    return shell;
}
