/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:24:39 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/01 16:51:57 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_command	*command_ini(char *op_com, t_env *env)
{
	t_command	*exec;

	op_com = parse_op(op_com);
	if (!op_com)
		return (NULL);
	exec = malloc(sizeof(t_command));
	if (!exec)
		return (NULL);
	exec->original_commands = args_split(op_com);
	free(op_com);
	if (!exec->original_commands)
	{
		free(exec);
		return (NULL);
	}
	exec->original_tokens = tokenization(exec->original_commands);
	if (!exec->original_tokens)
	{
		ft_free((void **)exec->original_commands);
		free(exec);
		return (NULL);
	}
	expand_env_vars(exec->original_commands, exec->original_tokens, env);
	del_quotes(exec->original_commands);
	return (exec);
}
