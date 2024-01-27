//
// Created by Anouar Zougrar on 8/12/2023.
//

#include <printf.h>
#include <stdlib.h>

#include "shell.h"
#include "commands_parser.h"
#include "commands.h"

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
        case CD:
            return execute_cd_command(command, shell);
        case LS:
            return execute_ls_command(command, shell);
        case PWD:
            return execute_pwd_command(command, shell);
        case EMPTY:
            return 1;
        case UNKNOWN:
        default:
            printf("unknown command\n");
            return 1;
    }
}

void print_prompt(struct Shell *shell) {
    const char *user = "DEBUG_ROOT";
    const char *host = "DEBUG_HOST";

    char *file_node_name = shell->current_directory->file_data->name;

    printf("%s@%s:%s$ ", user, host, file_node_name);
}

int run_shell(struct Shell *shell) {
    int status = 0;
    char *command_entry = NULL;

    do {
        print_prompt(shell);
        command_entry = read_command_line();

        struct Command command = parse_command(command_entry);

        status = exec_command(command, shell);

        // printf("\n-- debug tree --\n");
        // print_fs_tree(shell->root_directory, 0);

        free(command_entry);
        free(command.args);
    } while (status == 1);

    return 0;
}

struct Shell *shell_init() {
    struct File_node *root = create_file_node("/", DIRECTORY_TYPE);

    struct Shell *shell = malloc(sizeof(struct Shell));
    shell->root_directory = root;
    shell->current_directory = root;

    return shell;
}
