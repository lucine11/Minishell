#ifndef MINISHELL_H
# define MINISHELL_H


typedef struct			s_command 
{
	char				pipe;
	char				type_in;
	char				type_out;
	char				*cmd;
	int					fd_in;
	int					fd_out;
	int					return_value;
	int					pipe_fd[2];
}						t_command;
