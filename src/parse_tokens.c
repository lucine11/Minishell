/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 08:51:32 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/27 10:55:33 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	check_iflastop_pip(int *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (cmd[i - 1] && cmd[i - 1] == PIPELINE)
	{
		ft_printf(2, "minishell: parse error near `|'\n");
		return (true);
	}
	return (false);
}

static bool	check_for_maxheredoc(int *cmd)
{
	int	i;
	int	hd;

	i = 0;
	hd = 0;
	while (cmd[i])
	{
		if (cmd[i] == HER_SIGNAL)
			hd += 1;
		i++;
	}
	if (hd > 15)
	{
		exit_status = 2;
		ft_printf(2, "minishell: maximum here-document exceeded\n");
		return (false);
	}
	return (true);
}

static bool	check_for_filesop(int *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == RED_INPUT_SIGNAL && cmd[i + 1] != RED_INPUT_FILE)
			return (false);
		if (cmd[i] == RED_OUTPUT_SIGNAL && cmd[i + 1] != RED_OUTPUT_FILE)
			return (false);
		if (cmd[i] == APPEND_O_SIGNAL && cmd[i + 1] != APPEND_O_FILE)
			return (false);
		if (cmd[i] == HER_SIGNAL && cmd[i + 1] != HER_LIMITER)
			return (false);
		i++;
	}
	return (true);
}

bool	double_op(int *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == PIPELINE && cmd[i + 1] == PIPELINE)
		{
			ft_printf(2, "minishell: syntax error near unexpected token `|'\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_tokens(int *cmd)
{
	if (!double_op(cmd))
	{
		exit_status = 2;
		return (false);
	}
	if (check_iflastop_pip(cmd))
	{
		exit_status = 2;
		return (false);
	}
	if (!check_for_filesop(cmd))
	{
		exit_status = 2;
		ft_printf(2, "minishell: syntax error: near unexpected token\n");
		return (false);
	}
	if (!check_for_maxheredoc(cmd))
		return (false);
	return (true);
}
