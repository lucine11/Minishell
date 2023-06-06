/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 07:20:11 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/06 08:09:49 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	args_number(int *tokens)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == COM_ARGUMENT || tokens[i] == COM_NAME)
			j++;
		i++;
	}
	return (j);
}

char	**command_args(char **c_args, int *tokens, t_env *env, char *cmd)
{
	char	**args;
	int		i;
	int		na;

	args = split_path(env);
	if (!args && env && !cmd)
		return (NULL);
	ft_free((void **)args);
	na = args_number(tokens);
	if (!na)
		return (NULL);
	args = malloc(sizeof(char *) * (na + 1));
	if (!args)
		return (NULL);
	args[na] = NULL;
	i = -1;
	na = 0;
	while (c_args[++i])
		if (tokens[i] == COM_NAME || tokens[i] == COM_ARGUMENT)
			args[na++] = ft_strdup(c_args[i]);
	return (args);
}

int	check_env_buil(char **cmd_array, int *token_array)
{
	int	i;

	i = 0;
	while (cmd_array && cmd_array[i] && token_array && token_array[i] != COM_NAME)
		i++;
	if (!cmd_array[i])
		return (0);
	if (!ft_strcmp(cmd_array[i], "cd")
		|| !ft_strcmp(cmd_array[i], "export")
		|| !ft_strcmp(cmd_array[i], "unset")
		|| !ft_strcmp(cmd_array[i], "exit"))
		return (1);
	return (0);
}

void	launch_env_builtin(char **cmd_array, int *token_array, t_command *command)
{
	char	**arg_array;
	int		i;

	i = 0;
	if (!cmd_array || !token_array)
		return ;
	while (cmd_array[i] && token_array[i] != COM_NAME)
		i++;
	if (!cmd_array[i])
		return ;
	arg_array = command_args(cmd_array, token_array, NULL, NULL);
	if (!ft_strcmp(cmd_array[i], "cd"))
		{
            /* your handling code here */
        }
	else if (!ft_strcmp(cmd_array[i], "export"))
		{
            /* your handling code here */
        }
	else if (!ft_strcmp(cmd_array[i], "unset"))
		{
            /* your handling code here */
        }
	else if (!ft_strcmp(cmd_array[i], "exit"))
	{
		close(command->pipeline[0][1]);
		close(command->pipeline[1][0]);
		//
	}
	ft_free((void **)arg_array);
}

static void	check_builtins(char **cmd_array, int *token_array, t_command *command, int cmd_nb)
{
	char	**arg_array;

	arg_array = command_args(cmd_array, token_array, NULL, NULL);
	if (!ft_strcmp(arg_array[0], "echo"))
		{
            ft_echo(arg_array,token_array);
        }
	else if (!ft_strcmp(arg_array[0], "env"))
		{
            
        }
	else if (!ft_strcmp(arg_array[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(arg_array[0], "cd"))
		{
            //
        }
	else if (!ft_strcmp(arg_array[0], "export"))
		{
            //
        }
	else if (!ft_strcmp(arg_array[0], "unset"))
		{
            //
        }
	else if (!ft_strcmp(arg_array[0], "exit"))
	{
		close_fd(command->pipeline[cmd_nb % 2][0]);
		//
	}
	ft_free((void **)arg_array);
}

void	close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

void	launch_builtin(char **cmd_array, int *token_array, t_command *command, int cmd_num)
{
	if (command->pipeline[(cmd_num + 1) % 2][0] == -1
		|| command->pipeline[cmd_num % 2][1] == -1)
		return ;
	command->hold_pid[cmd_num] = fork();
	if (command->hold_pid[cmd_num] == 0)
	{
		dup2(command->pipeline[(cmd_num + 1) % 2][0], 0);
		dup2(command->pipeline[cmd_num % 2][1], 1);
		close_fd(command->pipeline[(cmd_num + 1) % 2][0]);
		close_fd(command->pipeline[cmd_num % 2][1]);
		check_builtins(cmd_array, token_array, command, cmd_num);
		close_fd(command->pipeline[cmd_num % 2][0]);
		//close_heredocs(command->heredoc_fd);
		ft_list_clear(command->env);
		ft_free_command(command, NULL, NULL);
		exit(exit_status);
	}
}

int	check_for_builtin(char **cmd_array, int *token_array)
{
	int	i;

	i = 0;
	while (cmd_array && cmd_array[i] && token_array && token_array[i] != COM_NAME && token_array[i] != COM_ARGUMENT)
		i++;
	if (!cmd_array[i])
		return (0);
	if (!ft_strcmp(cmd_array[i], "echo") || !ft_strcmp(cmd_array[i], "env")
		|| !ft_strcmp(cmd_array[i], "pwd") || !ft_strcmp(cmd_array[i], "cd")
		|| !ft_strcmp(cmd_array[i], "export") || !ft_strcmp(cmd_array[i], "unset")
		|| !ft_strcmp(cmd_array[i], "exit"))
		return (1);
	return (0);
}
