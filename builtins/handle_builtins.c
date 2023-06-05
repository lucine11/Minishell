/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 07:20:11 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/04 22:16:58 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	ft_free(void **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr && arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// }

// static char	**split_path(t_env *env)
// {
// 	char	**path;
// 	t_env	*ptr;

// 	ptr = env;
// 	while (ptr && ft_strcmp(ptr->var_name, "PATH"))
// 		ptr = ptr->next;
// 	path = NULL;
// 	if (ptr)
// 		path = ft_split(ptr->var_value, ':');
// 	return (path);
// }

// char	**command_args(char **c_args, int *tokens, t_env *env, char *cmd)
// {
// 	char	**args;
// 	int		i;
// 	int		na;

// 	args = split_path(env);
// 	if (!args && env && !cmd)
// 		return (NULL);
// 	ft_free((void **)args);
// 	na = get_arg_nb(tokens);
// 	if (!na)
// 		return (NULL);
// 	args = malloc(sizeof(char *) * (na + 1));
// 	if (!args)
// 		return (NULL);
// 	args[na] = NULL;
// 	i = -1;
// 	na = 0;
// 	while (c_args[++i])
// 		if (tokens[i] == COM_NAME || tokens[i] == COM_ARGUMENT)
// 			args[na++] = ft_strdup(c_args[i]);
// 	return (args);
// }

// int	check_env_buil(char **cmd_array, int *token_array)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_array && cmd_array[i] && token_array && token_array[i] != COM_NAME)
// 		i++;
// 	if (!cmd_array[i])
// 		return (0);
// 	if (!ft_strcmp(cmd_array[i], "cd")
// 		|| !ft_strcmp(cmd_array[i], "export")
// 		|| !ft_strcmp(cmd_array[i], "unset")
// 		|| !ft_strcmp(cmd_array[i], "exit"))
// 		return (1);
// 	return (0);
// }

// void	launch_env_builtin(char **cmd_array, int *token_array, t_execution *exec)
// {
// 	char	**arg_array;
// 	int		i;

// 	i = 0;
// 	if (!cmd_array || !token_array)
// 		return ;
// 	while (cmd_array[i] && token_array[i] != COM_NAME)
// 		i++;
// 	if (!cmd_array[i])
// 		return ;
// 	arg_array = command_args(cmd_array, token_array, NULL, NULL);
// 	if (!ft_strcmp(cmd_array[i], "cd"))
// 		{
//             /* your handling code here */
//         }
// 	else if (!ft_strcmp(cmd_array[i], "export"))
// 		{
//             /* your handling code here */
//         }
// 	else if (!ft_strcmp(cmd_array[i], "unset"))
// 		{
//             /* your handling code here */
//         }
// 	else if (!ft_strcmp(cmd_array[i], "exit"))
// 	{
// 		close(exec->pipe_fd[0][1]);
// 		close(exec->pipe_fd[1][0]);
// 		//
// 	}
// 	ft_free((void **)arg_array);
// }

// static void	launch_builtin(char **cmd_array, int *token_array, t_execution *exec, int cmd_nb)
// {
// 	char	**arg_array;

// 	arg_array = get_command_args(cmd_array, token_array, NULL, NULL);
// 	if (!ft_strcmp(arg_array[0], "echo"))
// 		{
            
//         }
// 	else if (!ft_strcmp(arg_array[0], "env"))
// 		{
            
//         }
// 	else if (!ft_strcmp(arg_array[0], "pwd"))
// 		ft_pwd();
// 	else if (!ft_strcmp(arg_array[0], "cd"))
// 		{
//             //
//         }
// 	else if (!ft_strcmp(arg_array[0], "export"))
// 		{
//             //
//         }
// 	else if (!ft_strcmp(arg_array[0], "unset"))
// 		{
//             //
//         }
// 	else if (!ft_strcmp(arg_array[0], "exit"))
// 	{
// 		sec_close(exec->pipe_fd[cmd_nb % 2][0]);
// 		//
// 	}
// 	ft_free((void **)arg_array);
// }

// void	sec_close(int fd)
// {
// 	if (fd != -1)
// 		close(fd);
// }

// void	launch_builtin_execution(char **cmd_array, int *token_array, t_execution *exec, int cmd_num)
// {
// 	if (exec->pipe_fd[(cmd_num + 1) % 2][0] == -1
// 		|| exec->pipe_fd[cmd_num % 2][1] == -1)
// 		return ;
// 	exec->cpid[cmd_num] = fork();
// 	if (exec->cpid[cmd_num] == 0)
// 	{
// 		dup2(exec->pipe_fd[(cmd_num + 1) % 2][0], 0);
// 		dup2(exec->pipe_fd[cmd_num % 2][1], 1);
// 		sec_close(exec->pipe_fd[(cmd_num + 1) % 2][0]);
// 		sec_close(exec->pipe_fd[cmd_num % 2][1]);
// 		launch_builtin(cmd_array, token_array, exec, cmd_num);
// 		sec_close(exec->pipe_fd[cmd_num % 2][0]);
// 		close_heredocs(exec->heredoc_fd);
// 		ft_envlst_clear(exec->env);
// 		free_execution(exec, NULL, NULL);
// 		exit(exit_status);
// 	}
// }

// int	is_builtin(char **cmd_array, int *token_array)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd_array && cmd_array[i] && token_array && token_array[i] != COM_NAME && token_array[i] != COM_ARGUMENT)
// 		i++;
// 	if (!cmd_array[i])
// 		return (0);
// 	if (!ft_strcmp(cmd_array[i], "echo") || !ft_strcmp(cmd_array[i], "env")
// 		|| !ft_strcmp(cmd_array[i], "pwd") || !ft_strcmp(cmd_array[i], "cd")
// 		|| !ft_strcmp(cmd_array[i], "export") || !ft_strcmp(cmd_array[i], "unset")
// 		|| !ft_strcmp(cmd_array[i], "exit"))
// 		return (1);
// 	return (0);
// }
