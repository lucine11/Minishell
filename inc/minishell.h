#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdbool.h>

#define MAX_ARGS 10

typedef struct command {
    char **args;
    bool background;
    char *input_file;
    char *output_file;
    bool append;
    struct command *next;
} command_t;

command_t *parse_input(char *input);
void free_command(command_t *cmd);

#endif
