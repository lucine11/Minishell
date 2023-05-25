/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:36:52 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/10 15:36:52 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include <unistd.h>
#include <stdbool.h>

extern int	exit_status;

#define OP_ERROR "minishell:\
	syntax error near unexpected token `%c%c'\n"

typedef struct s_token 
{
    char *value;
    bool is_quoted;
    struct s_token *next;
} t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

t_token *parse_quotes(char *line);
bool is_whitespace(char c);
t_token	*breakdown_line(char *line);
bool		check_characters(const char *line, const char *charset);
bool		check_pipe(const char *line);
t_token *new_token(char *value, bool is_quoted);
bool        isempty_line(char *line);
void	change_value_state(int *state, int c);
char	**args_split(char *cmd);
char	*parse_op(char *cmd);
bool	check_for_pipe(char c);
bool	check_for_redirection(char c);
bool	check_for_space(char c);
void	ft_listadd_back(t_env **env, t_env *new_env);
t_env	*ft_list_last(t_env *env);
int	ft_list_size(t_env *env);
t_env	*ft_list_search(t_env *env, char *searched);
t_env	*get_env_variables(char **envp);
void	get_prompt(t_env *env);
#endif
