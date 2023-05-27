/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:07:18 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/27 03:31:21 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	next_arg_len(char *cmd)
{
	int	i;
	int	quote_state;

	quote_state = 0;
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			change_value_state(&quote_state, cmd[i]);
		i++;
		if (is_space(cmd[i]) && !quote_state)
			break ;
	}
	return (i);
}

static int	arg_cnt(char *cmd)
{
	int	i;
	int	nb;
	int	quote_state;

	quote_state = 0;
	nb = 0;
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			change_value_state(&quote_state, cmd[i]);
		i++;
		if (is_space(cmd[i]) && !quote_state)
		{
			while (cmd[i] && is_space(cmd[i]))
				i++;
			if (cmd[i])
				nb++;
		}
	}
	return (nb + (quote_state == 0));
}

char	**args_split(char *cmd)
{
	char	**args;
	int		nb_args;
	int		len_arg;
	int		i;

	while (cmd && *cmd && is_space(*cmd))
		cmd++;
	nb_args = arg_cnt(cmd);
	args = malloc((nb_args + 1) * sizeof(char *));
	args[nb_args] = NULL;
	i = 0;
	while (i < nb_args)
	{
		len_arg = next_arg_len(cmd);
		args[i] = ft_substr(cmd, 0, len_arg);
		cmd += len_arg + (cmd[len_arg] != '\0');
		while (*cmd && is_space(*cmd))
			cmd++;
		i++;
	}
	return (args);
}
