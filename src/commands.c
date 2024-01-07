//
// Created by Anouar Zougrar on 7/1/2024.
//

#ifndef FILE_SYSTEM__MSIP_COMMANDS_C
#define FILE_SYSTEM__MSIP_COMMANDS_C

#include <string.h>

#include "commands.h"

const char *exit_command = "exit";

enum Command parse_command_string(char *command_string) {
    if (strcmp(command_string, "exit\n") == 0) {
        return EXIT;
    } else {
        return UNKNOWN;
    }
}

#endif //FILE_SYSTEM__MSIP_COMMANDS_C
