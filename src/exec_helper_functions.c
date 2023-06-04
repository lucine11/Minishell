/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 02:16:05 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/03 18:17:01 by lahamoun         ###   ########.fr       */
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
