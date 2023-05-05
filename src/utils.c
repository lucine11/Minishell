#include "../inc/minishell.h"

bool is_whitespace(char c) 
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

t_token *new_token(char *value, bool is_quoted) {
    t_token *token = malloc(sizeof(t_token));
    if (!token) 
    {
        printf("minishell: allocation error\n");
        exit(EXIT_FAILURE);
    }
    token->value = value;
    token->is_quoted = is_quoted;
    token->next = NULL;
    return token;
}
