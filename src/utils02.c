/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:58:36 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/24 15:21:40 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	check_for_pipe(char c)
{
	if (c == '|')
		return (true);
	return (false);
}

bool	check_for_redirection(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

bool	check_for_space(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}

t_env	*ft_list_search(t_env *env, char *searched)
{
	t_env	*head;

	head = env;
	while (head != NULL)
	{
		if (!ft_strcmp(head->name, searched))
			return (head);
		head = head->next;
	}
	return (NULL);
}

int	ft_list_size(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		env = env->next;
		i++;
	}
	return (i);
}