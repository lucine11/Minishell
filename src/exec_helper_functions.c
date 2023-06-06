/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 02:16:05 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/06 08:09:49 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	com_cnt(char **args, int *tokens)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (args[i] && tokens[i])
	{
		if (tokens[i] == PIPELINE)
			cnt++;
		i++;
	}
	return (cnt + 1);
}

void	ft_free_command(t_command *command, char *path, char **args)
{
	free(path);
	ft_free((void **)args);
	ft_free((void **)command->command_segments);
	ft_free((void **)command->token_types);
	free(command->original_commands);
	ft_free((void **)command->original_commands);
	free(command->hold_pid);
	free(command);
}
void	ft_list_clear(t_env **env)
{
	t_env	*cur;
	t_env	*tmp;

	if (!*env)
		return ;
	cur = *env;
	while (cur != NULL)
	{
		tmp = cur;
		cur = cur->next;
		free (tmp->name);
		if (tmp->value)
			free (tmp->value);
		free (tmp);
	}
	*env = NULL;
}

void	close_all(int pipe_fd[2][2], int cmd_nb)
{
	close_fd(pipe_fd[(cmd_nb + 1) % 2][0]);
	close_fd(pipe_fd[cmd_nb % 2][0]);
	close_fd(pipe_fd[cmd_nb % 2][1]);
}