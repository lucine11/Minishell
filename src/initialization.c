/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:24:39 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/02 15:39:58 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// char **ft_subarray(char **array, int start, int length)
// {
// 	int i;
// 	char **subarray = malloc((length + 1) * sizeof(char *));
// 	if (!subarray)
// 		return NULL;
	
// 	for (i = 0; i < length; i++)
// 	{
// 		subarray[i] = ft_strdup(array[start + i]);
// 		if (!subarray[i])
// 		{
// 			while (i--)
// 				free(subarray[i]);
// 			free(subarray);
// 			return NULL;
// 		}
// 	}
// 	subarray[length] = NULL;
	
// 	return subarray;
// }

// char ***split_commands(char **original_commands, int *original_tokens)
// {
// 	int i = 0, j = 0,
// 	int start = 0;
// 	int com_count = 0;
// 	char ***command_segments = NULL;
	
// 	// calculate the number of command segments
// 	while (original_tokens[i] != NULL_TOKEN)
// 	{
// 		if (original_tokens[i] == PIPELINE)
// 			com_count++;
// 		i++;
// 	}
// 	com_count++;
// 	command_segments = malloc((com_count + 1) * sizeof(char **));
// 	if (!command_segments)
// 		return NULL;
// 	command_segments[com_count] = NULL;
// 	i = 0;
// 	while (original_tokens[i] != NULL_TOKEN)
// 	{
// 		if (original_tokens[i] == PIPELINE)
// 		{
// 			command_segments[j] = ft_subarray(original_commands, start, i - start);
// 			start = i + 1;
// 			j++;
// 		}
// 		i++;
// 	}
// 	command_segments[j] = ft_subarray(original_commands, start, i - start); // Last command segment
	
// 	return command_segments;
// }

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
