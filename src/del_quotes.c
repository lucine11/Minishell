/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:39:43 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/07 08:39:38 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*remove_them(char *token, int *i)
{
	char	*new_tok;
	char	quote;
	char	*tmp[2];
	int		j;

	quote = token[*i];
	j = *i + 1;
	while (token[j] && token[j] != quote)
		j++;
	tmp[0] = ft_substr(token, 0, *i);
	tmp[1] = ft_substr(token, *i + 1, j - *i - 1);
	new_tok = ft_strjoin(tmp[0], tmp[1]);
	free (tmp[0]);
	free (tmp[1]);
	*i = j - 2;
	tmp[0] = ft_strjoin(new_tok, token + j + 1);
	free (token);
	free (new_tok);
	token = ft_strdup(tmp[0]);
	free (tmp[0]);
	return (token);
}

static char	*remove_token_quotes(char *token)
{
	int		i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
			token = remove_them(token, &i);
		i++;
	}
	return (token);
}

void	del_quotes(char **com)
{
	int	i;

	i = 0;
	while (com[i])
	{
		if (((com[i] && ft_strchr(com[i], '\''))
				|| (com[i] && ft_strchr(com[i], '"'))))
			com[i] = remove_token_quotes(com[i]);
		i++;
	}
}
