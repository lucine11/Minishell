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
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <stdarg.h>
#include <fcntl.h>
#include <stdbool.h>

extern int	exit_status;

#define OP_ERROR "minishell:\
	syntax error near unexpected token `%c%c'\n"

typedef enum CommandType
{
    COM_ARGUMENT = 1,       // The argument of a command
    COM_NAME = 2,          // The name of the command to be executed
    NULL_TOKEN = 0,       // placeholder for a token that doesn't exist
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
    char    ****command_array;
	char	***command_segments;
	int		**token_types;
	char	**original_commands;
	int		*original_tokens;
    int     *hold_pid;
	int		com_count;
    int     heredoc[15][2];
    int     pipeline[2][2];
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
void	ft_list_clear(t_env **env);
t_command	*command_ini(char *op_com, t_env *env);
bool execute_builtin(char **cmds, int *toks, t_env *env);
void    ft_pwd(void);
void    ft_echo(char **cmd, int *tok);
int **split_tokens(int *original_tokens);
int	com_cnt(char **args, int *tokens);
int heredoc_handler(t_command *command);
int	check_env_buil(char **cmd_array, int *token_array);
void	launch_env_builtin(char **cmd_array, int *token_array, t_command *command);
int	check_for_builtin(char **cmd_array, int *token_array);
void	ft_free_command(t_command *command, char *path, char **args);
void	launch_builtin(char **cmd_array, int *token_array, t_command *command, int cmd_num);
char	*get_thepath(char **cmd_arg, int *tokens, t_env *env);
char	**split_path(t_env *env);
char	**command_args(char **c_args, int *tokens, t_env *env, char *cmd);
void	close_fd(int fd);
void	execute_commands(char *path, char **args, int cmd_nb, t_command *command);
char	**transform_envp(t_env *env);
void	close_all(int pipe_fd[2][2], int cmd_nb);
void	command_initial(char *op_com, t_env **env);
void	handle_redirections(t_command *exec, int cmd_nb);
#endif
