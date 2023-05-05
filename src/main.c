#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_token *parse_input(char *line)
{
    int i = 0;
    int start = -1;
    char quote = '\0';
    t_token *head = NULL;
    t_token *tail = NULL;
    t_token *new = NULL;

    while (line[i] != '\0')
    {
        if (quote)
        {
            if (line[i] == quote)
            {
                quote = '\0';
                new = new_token(ft_strndup(&line[start], i - start), true);
                if (!head)
                    head = new;
                else
                    tail->next = new;
                tail = new;
                start = -1;
            }
        }
        else if (line[i] == '\'' || line[i] == '\"')
        {
            quote = line[i];
            if (start >= 0)
            {
                new = new_token(ft_strndup(&line[start], i - start), false);
                if (!head)
                    head = new;
                else
                    tail->next = new;
                tail = new;
            }
            start = i + 1;
        }
        else if (is_whitespace(line[i]))
        {
            if (start >= 0)
            {
                new = new_token(ft_strndup(&line[start], i - start), false);
                if (!head)
                    head = new;
                else
                    tail->next = new;
                tail = new;
                start = -1;
            }
        }
        else if (start < 0)
            start = i;
        i++;
        if (quote == '\0' && (line[i] == '\'' || line[i] == '\"'))
        {
            quote = line[i];
            start = i + 1;
            i++;
        }
    }
    if (start >= 0)
    {
        new = new_token(ft_strndup(&line[start], i - start + (quote != '\0')), quote != '\0');
        if (!head)
            head = new;
        else
            tail->next = new;
    }
    return (head);
}

//test
void print_tokens(t_token *tokens) 
{
    t_token *tmp = tokens;
    while (tmp) 
    {
        printf("Token: %s (quoted: %s)\n", tmp->value, tmp->is_quoted ? "yes" : "no");
        tmp = tmp->next;
    }
}

int main() 
{
    char *line;
    t_token *tokens;

    while (1) 
    {
        line = readline("minishell$ ");
        if (line == NULL) 
        {
            printf("\n");
            break;
        }
        if (*line) 
            add_history(line);
        tokens = parse_input(line);
        print_tokens(tokens);
        free(line);     
    }

    return 0;
}
