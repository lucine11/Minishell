/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:36:23 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/10 16:00:13 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	check_unclosed_quote(const char *line)
{
	int		i;
	int		state;

	i = 0;
	state = 0;
	while (line[i])
	{
		change_value_state(&state, line[i]);
		i++;
	}
	if (state == 1)
	{
		ft_printf(2, "minishell: ' not closed\n");
		return (false);
	}
	else if (state == 2)
	{
		ft_printf(2, "minishell: \" not closed\n");
		return (false);
	}
	return (true);
}

static bool	check_operators(const char *line, const char c, const int nb)
{
	int		i;
	int		state;
	int		cnt_operator;

	i = -1;
	state = 0;
	while (line[++i])
	{
        change_value_state(&state, line[i]);
		cnt_operator = 0;
		while (line[i] && state == 0 && line[i] == c)
		{
			cnt_operator++;
			i++;
			change_value_state(&state, line[i]);
		}
		if (state == 0 && cnt_operator > nb)
		{
			ft_printf(2, OP_ERROR, c, c);
			return (false);
		}
		if (!line[i])
			break ;
	}
	return (true);
}

static bool	check_unsupported_operators(const char *line)
{
	int		i;
	int		state;

	i = 0;
	state = 0;
	while (line[i])
	{
		change_value_state(&state, line[i]);
		if ((state == 0 && line[i] == '>') || (state == 0 && line[i] == '<'))
		{
			if ((line[i] == '>' && line[i + 1] == '<')
				|| (line[i] == '<' && line[i + 1] == '>'))
			{
				ft_printf(2, "minishell: syntax error: unexpected operator\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	isempty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (line[i] == 0)
		return (true);
	return (false);
}

t_token	*breakdown_line(char *line)
{
    t_token *tokens = (NULL);

	if (!line || isempty_line(line))
		return (NULL);
	if (!check_unclosed_quote(line) || !check_operators(line, '<', 2) || !check_operators(line, '>', 2)
		|| !check_operators(line, '|', 1) || !check_characters(line, ";\\&")
		|| !check_unsupported_operators(line) || !check_pipe(line))
	{
		exit_status = 2;
		return (NULL);
	}
    tokens = parse_quotes(line);
	return (tokens);
}