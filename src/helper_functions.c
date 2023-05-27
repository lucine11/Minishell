/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:36:08 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/27 08:19:25 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool is_whitespace(char c) 
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

t_token *new_token(char *value, bool is_quoted) 
{
    t_token *token = malloc(sizeof(t_token));
    if (!token) 
    {
        printf("minishell: allocation error\n");
        exit(EXIT_FAILURE);
    }
    token->value = value;
    token->is_quoted = is_quoted;
    token->next = NULL;
    return (token);
}

void	change_value_state(int *state, int c)
{
	if (c == '\'')
	{
		if (*state == 1)
			*state = 0;
		else if (*state == 0)
			*state = 1;
	}
	if (c == '\"')
	{
		if (*state == 2)
			*state = 0;
		else if (*state == 0)
			*state = 2;
	}
}

bool	check_characters(const char *line, const char *charset)
{
	int		i;
	int		state;
	int		j;

	i = 0;
	state = 0;
	while (line[i])
	{
		change_value_state(&state, line[i]);
		j = 0;
		while (state == 0 && charset[j])
		{
			if (line[i] == charset[j])
			{
				ft_printf(2, "minishell: syntax error: `%c' in input\n", charset[j]);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_pipe(const char *line)
{
	if (line[0] == '|')
	{
		ft_printf(2, "minishell: syntax error near unexpected token `|'\n");
		return (false);
	}
	return (true);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
