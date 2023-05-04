#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_token 
{
    char *value;
    bool is_quoted;
    struct s_token *next;
} t_token;

t_token *parse_input(char *line);
bool is_whitespace(char c);
t_token *new_token(char *value, bool is_quoted);

#endif
