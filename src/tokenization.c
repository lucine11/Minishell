/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:42:52 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/27 11:46:49 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	define_token_operator(char *cmd, int *comtype)
{
	if (cmd[0] == '|')
		*comtype = PIPELINE;
	else if (ft_strlen(cmd) > 1 && cmd[0] == '<')
		*comtype = HER_SIGNAL;
	else if (ft_strlen(cmd) > 1 && cmd[0] == '>')
		*comtype = APPEND_O_SIGNAL;
	else if (cmd[0] == '<')
		*comtype = RED_INPUT_SIGNAL;
	else if (cmd[0] == '>')
		*comtype = RED_OUTPUT_SIGNAL;
}

static bool	is_operator(char c, char *op)
{
	int	i;

	i = 0;
	while (op[i])
	{
		if (op[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static void	define_token_type(char **cmd, int **comtype, int i, bool *cmd_in_pipe)
{
    if (i == 0 && cmd[i][0] == '|')
    {
		ft_printf(2,"minishell: syntax error near unexpected token `|'\n");
		return;
	}
	if (is_operator(cmd[i][0], "<>|"))
	{
		define_token_operator(cmd[i], &(*comtype)[i]);
		if ((*comtype)[i] == PIPELINE)
			*cmd_in_pipe = false;
	}
	else if (i > 0 && (*comtype)[i - 1] == HER_SIGNAL)
		(*comtype)[i] = HER_LIMITER;
	else if (i > 0 && (*comtype)[i - 1] == RED_INPUT_SIGNAL)
		(*comtype)[i] = RED_INPUT_FILE;
	else if (i > 0 && (*comtype)[i - 1] == RED_OUTPUT_SIGNAL)
		(*comtype)[i] = RED_OUTPUT_FILE;
	else if (i > 0 && (*comtype)[i - 1] == APPEND_O_SIGNAL)
		(*comtype)[i] = APPEND_O_FILE;
	else if ((i > 0 && (*comtype)[i - 1] == COM_NAME)
			|| (i > 0 && (*comtype)[i - 1] == COM_ARGUMENT) || *cmd_in_pipe == true)
		(*comtype)[i] = COM_ARGUMENT;
	else
	{
		(*comtype)[i] = COM_NAME;
		*cmd_in_pipe = true;
	}
}

int	*tokenization(char **cmd)
{
	bool	cmd_in_pipe;
	int		*comtype;
	int		i;

	comtype = ft_calloc(sizeof(int), ft_arrlen(cmd) + 1);
	if (!comtype)
		return (NULL);
	i = 0;
	cmd_in_pipe = false;
	while (cmd[i])
	{
		define_token_type(cmd, &comtype, i, &cmd_in_pipe);
		i++;
	}
	if (check_tokens(comtype))
		return (comtype);
	exit_status = 2;
	free(cmd);
	return (NULL);
}
