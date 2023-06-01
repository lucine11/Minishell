/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:39:43 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/01 17:18:40 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


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
