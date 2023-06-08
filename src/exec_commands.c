/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:02:36 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/07 06:57:44 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_directory(char *cmd)
{
	DIR	*dirp;

	if (!cmd)
		return (0);
	dirp = opendir(cmd);
	if (dirp)
	{
		ft_printf(2, "minishell: %s: Is a directory\n", cmd);
		exit_status = 126;
		closedir(dirp);
		return (1);
	}
	return (0);
}

void	execute_commands(char *path, char **args, int cmd_nb, t_command *command)
{
	char	**envp;

	if (command->pipeline[(cmd_nb + 1) % 2][0] == -1
		|| command->pipeline[cmd_nb % 2][1] == -1 || !args || is_directory(args[0]))
		return ;
	if (path == NULL && args[0])
	{
		ft_printf(2, "minishell: %s: command not found\n", args[0]);
		return ;
	}
	command->hold_pid[cmd_nb] = fork();
	if (command->hold_pid[cmd_nb] == 0)
	{
		//this is just a test 
		dup2(command->pipeline[(cmd_nb + 1) % 2][0], 0);
		dup2(command->pipeline[cmd_nb % 2][1], 1);
		close_all(command->pipeline, cmd_nb);
		envp = transform_envp(*command->env);
		execve(path, args, envp);
		ft_list_clear((command)->env);
		ft_free((void **)envp);
		ft_free_command(command, path, args);
		exit(1);
	}
}