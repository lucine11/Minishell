/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 02:16:05 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/03 18:25:59 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	wait_children(int *holdpid, int cmds_cnt)
{
	int	pid;
	int	status;

	pid = 0;
	while (pid < cmds_cnt)
	{
		if (holdpid[pid] != -1)
		{
			waitpid(holdpid[pid], &status, 0);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == 2)
					exit_status = 130;
				else if (WTERMSIG(status) == 3)
					exit_status = 131;
				else if (WTERMSIG(status) == 11)
					exit_status = 139;
			}
		}
		pid++;
	}
}

static void	iterate_over_commands(t_command *command, int cmd, char *cmd_path, char **cmd_args)
{
	while (command->command_segments[cmd])
	{
		handle_redirections(command, cmd);
		cmd_path = NULL;
		cmd_args = NULL;
		if (check_for_builtin(command->command_segments[cmd], command->token_types[cmd]))
			launch_builtin(command->command_segments[cmd], command->token_types[cmd], command, cmd);
		else
		{
			cmd_path = get_thepath(command->command_segments[cmd],
					command->token_types[cmd], *command->env);
			cmd_args = command_args(command->command_segments[cmd],
					command->token_types[cmd], *command->env, cmd_path);
			execute_commands(cmd_path, cmd_args, cmd, command);
			if (cmd < command->com_count - 1)
			{
				free(cmd_path);
				ft_free((void **)cmd_args);
			}
		}
		close_fd(command->pipeline[(++cmd % 2)][0]);
		close_fd(command->pipeline[(cmd + 1) % 2][1]);
	}
	wait_children(command->hold_pid, command->com_count);
	//still need to get the last command
}

static void	launch_command(t_command *command)
{
	command->pipeline[0][0] = -1;
	command->pipeline[0][1] = -1;
	command->pipeline[1][0] = -1;
	command->pipeline[1][1] = -1;
	if (check_env_buil(command->command_segments[0], command->token_types[0]) && command->com_count == 1)
	{
		handle_redirections(command, 0);
		launch_env_builtin(command->command_segments[0], command->token_types[0], command);
		close_fd(command->pipeline[0][1]);
		close_fd(command->pipeline[1][0]);
		return ;
	}
	else
		iterate_over_commands(command, 0, NULL, NULL);
	//handle signals 
}

void	command_initial(char *op_com, t_env **env)
{
	t_command	*command;
	int		i;

	command = command_ini(op_com, *env);
	if (!command || !command->original_tokens)
		return ;
	command->env = env;
	command->com_count = com_cnt(command->original_commands, command->original_tokens);
	command->hold_pid = malloc(sizeof(int) * (command->com_count + 1));
	command->hold_pid = malloc(sizeof(int) * (command->com_count + 1));
	if (command->hold_pid)
	{
		i = 0;
		while (i < command->com_count)
			command->hold_pid[i++] = -1;
		command->hold_pid[i] = 0;
		launch_command(command);
	}
	//ft_free_command(command, NULL, NULL);
}