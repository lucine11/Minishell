/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 02:17:00 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/30 02:35:33 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	expand(char **cmd, int *tokens, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
			cmd[i] = expansion(cmd[i], env);
		j = 0;
		while (cmd[i][j])
			if (cmd[i][j] != ' ' || !(cmd[i][j] >= 9 && cmd[i][j] <= 13))
				break ;
		if (!cmd[i][j])
			tokens[i] = ' ';
		i++;
	}
}
static char	*expansion(char *tok, t_env *env)
{
	int		i;
	int		state;

	i = 0;
	state = 0;
	while (i != -1 && tok[i])
	{
		chg_qte_state(&state, tok[i]);
		if (tok[i] == '$' && state != 1 && tok[i + 1] == '?')
		{
            //replece it before checking ..
			if (tok[i] == '$' || tok[i] == '"' || tok[i] == '\'')
				continue ;
			else if (tok[i] == 0)
				break ;
		}
		i++;
	}
	return (tok);
}