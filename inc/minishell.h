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
#include <stdarg.h>
#include <stdbool.h>

extern int	exit_status;

#define OP_ERROR "minishell:\
	syntax error near unexpected token `%c%c'\n"

typedef enum CommandType
{
    COM_ARGUMENT = 1,       // The argument of a command
    COM_NAME = 2,          // The name of the command to be executed
    NULL_TOKEN = 32,       // placeholder for a token that doesn't exist
    RED_INPUT_SIGNAL = 3,  // A signal to redirect input ("<")
    RED_INPUT_FILE = 4,    // The file to redirect input from
    RED_OUTPUT_SIGNAL = 5, // A signal to redirect output (">")
    RED_OUTPUT_FILE = 6,   // The file to redirect output to
    HER_SIGNAL = 7,        // A signal for here-document input ("<<")
    HER_LIMITER = 8,       // The delimiter of a here-document
    APPEND_O_SIGNAL = 9,   // A signal to append output (">>")
    APPEND_O_FILE = 10,    // The file to append output to
    PIPELINE = 11,           // A signal for pipelining commands ("|")
} CommandType;


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

typedef struct s_command
{
	char	**command_segments;
	int		**token_types;
	char	**original_commands;
	int		*original_tokens;
	int		com_count;
	t_env	**env;
}	t_command;

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
int		ft_arrlen(char **arr);
bool	check_tokens(int *cmd);
int	    *tokenization(char **cmd);
char	*ft_strjoin_many(int num_args, ...);
void	expand_env_vars(char **cmd, int *tokens, t_env *env);
char *ft_strjoin_char(const char *s1, const char *s2, char c);
void	del_quotes(char **com);
void	ft_free(void **array);
t_command	*command_ini(char *op_com, t_env *env);
bool execute_builtin(char **cmds, int *toks, t_env *env);
void    ft_pwd(void);
void    ft_echo(char **cmd, int *tok);

#endif
