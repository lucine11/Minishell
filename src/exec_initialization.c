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
	
	if (command->hold_pid)
	{
		i = 0;
		while (i < command->com_count)
			command->hold_pid[i++] = -1;
		command->hold_pid[i] = 0;
	
	}
	//free_command(command);
}