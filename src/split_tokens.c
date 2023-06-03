/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:45 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/03 00:56:17 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int *ft_subarray_int(int *array, int start, int length)
{
	int i;
	int *subarray = malloc((length + 1) * sizeof(int));
	if (!subarray)
		return NULL;
	
	for (i = 0; i < length; i++)
	{
		subarray[i] = array[start + i];
	}
	subarray[length] = NULL_TOKEN;
	
	return subarray;
}

int **split_tokens(int *original_tokens)
{
	int i = 0, j = 0;
	int start = 0;
	int com_count = 0;
	int **token_types = NULL;
	
	while (original_tokens[i] != NULL_TOKEN)
	{
		if (original_tokens[i] == PIPELINE)
			com_count++;
		i++;
	}
	com_count++;
	token_types = malloc((com_count + 1) * sizeof(int *));
	if (!token_types)
		return NULL;
	token_types[com_count] = NULL;
	i = 0;

	while (original_tokens[i] != NULL_TOKEN)
	{
		if (original_tokens[i] == PIPELINE)
		{
			token_types[j] = ft_subarray_int(original_tokens, start, i - start);
			start = i + 1;
			j++;
		}
		i++;
	}
	token_types[j] = ft_subarray_int(original_tokens, start, i - start);
	
	return token_types;
}
