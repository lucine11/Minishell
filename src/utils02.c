/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:06:33 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/24 16:06:39 by lahamoun         ###   ########.fr       */
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

t_env	*ft_list_last(t_env *env)
{
	t_env	*last;

	last = env;
	if (env == NULL)
		return (NULL);
	while (env != NULL)
	{
		last = env;
		env = env->next;
	}
	return (last);
}

void	ft_listadd_back(t_env **env, t_env *new_env)
{
	t_env	*last;

	if (!new_env || !env)
		return ;
	if (*env == NULL)
		*env = new_env;
	else
	{
		last = ft_list_last(*env);
		last->next = new_env;
		new_env->prev = last;
	}
}
