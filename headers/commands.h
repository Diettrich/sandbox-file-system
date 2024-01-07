//
// Created by Anouar Zougrar on 7/1/2024.
//

#ifndef FILE_SYSTEM__MSIP_COMMANDS_H
#define FILE_SYSTEM__MSIP_COMMANDS_H

enum Command {
    UNKNOWN,
    EXIT,
};

enum Command parse_command_string(char *command_string);

#endif //FILE_SYSTEM__MSIP_COMMANDS_H
