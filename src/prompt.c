/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:17:42 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/25 15:30:48 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ft_lst_search(t_env *env, char *searched)
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

