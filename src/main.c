/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:07:45 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/27 03:33:30 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int exit_status;

t_token *parse_quotes(char *line)
{
    int i = 0;
    int start = -1;
    char quote = '\0';
    t_token *head = NULL;
    t_token *tail = NULL;
    t_token *new = NULL;

    while (line[i])
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
        new = new_token(ft_strndup(&line[start], i - start), false);
        if (!head)
            head = new;
        else
            tail->next = new;
    }
    return (head);
}

void print_tokens(t_token *tokens) 
{
    t_token *tmp = tokens;
    while (tmp) 
    {
        printf("Token: %s (quoted: %s)\n", tmp->value, tmp->is_quoted ? "yes" : "no");
        tmp = tmp->next;
    }
}
// static void	check_args(int ac, char **av)
// {
// 	(void)av;
// 	if (ac > 1)
// 	{
// 		printf("minishell: too many args\n");
// 		exit (127);
// 	}
// }

void free_args(char **args)
{
    int i = 0;
    while(args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}
int main(int ac, char **av, char **envp)
{
    (void)envp;
    (void)ac;
    (void)av;
    char *line;
    t_token *tokens;
    char **args;
    int *comtype;

    exit_status = 0;
    // check_args(ac, av);
    while (1) 
    {
        line = readline("minishell$ ");
        if (*line) 
            add_history(line);
        tokens = breakdown_line(line);
        if (tokens)
        {
            while (tokens != NULL)
            {
                tokens->value = parse_op(tokens->value);
                args = args_split(tokens->value);

                comtype = tokenization(args);
                if (comtype) {
                    int i = 0;
                    while (args[i]) 
                    {
                        printf("Arg[%d]: %s\n", i, args[i]);
                        printf("Comtype[%d]: %d\n", i, comtype[i]);
                        i++;
                    }
                    free(comtype);
                } else {
                    printf("Tokenization failed.\n");
                }

                tokens = tokens->next;
                free_args(args);
            }
        }
        free(line);
    }
    return 0;
}


// int main(int ac, char **av, char **envp)
// {
//     (void)envp;
//     (void)ac;
//     (void)av;
//     char *line;
//     t_token *tokens;
//     t_env *env_list;
    
//     env_list = get_env_variables(envp);
//     get_prompt(env_list);
//     exit_status = 0;
//     while (1) 
//     {
//         line = readline("$ ");
//         if (*line) 
//             add_history(line);
//         tokens = breakdown_line(line);
//     if (tokens)
//     {
//         char *parsed_line = parse_op(line);
//         printf("Parsed line: %s\n", parsed_line);
//         free(parsed_line);
//         print_tokens(tokens);
//     }
//     }
//     return 0;
// }

// int main(int ac, char **av, char **envp)
// {
//     (void)envp;
//     (void)ac;
//     (void)av;
//     char *line;
//     t_token *tokens;
//     char **args;

//     exit_status = 0;
//     // check_args(ac, av);
//     while (1) 
//     {
//         line = readline("minishell$ ");
//         if (*line) 
//             add_history(line);
//         tokens = breakdown_line(line);
//         if (tokens)
//         {
//             while (tokens != NULL)
//             {
//                 tokens->value = parse_op(tokens->value);
//                 args = args_split(tokens->value);
        
//                 int i = 0;
//                 while (args[i]) 
//                 {
//                     printf("Arg[%d]: %s\n", i, args[i]);
//                     i++;
//                 }

//                 tokens = tokens->next;
//                 free_args(args);
//             }
//         }
//         free(line);
//     }
//     return 0;
// }
