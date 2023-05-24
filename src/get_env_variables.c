/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:24:28 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/24 16:49:52 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ft_list_new(char *str)
{
	t_env	*new;

	new = ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (0);
	if (!ft_strchr(str, '='))
	{
		new->name = ft_strdup(str);
		if (!new->name)
			return (0);
		new->value = NULL;
	}
	else
		create_and_assign(str, &new);
	return (new);
}

t_env	*get_env_variables(char **envp)
{
	int		i;
	t_env	*root;
	t_env	*new;

	i = 0;
	root = NULL;
	while (envp[i])
	{
		new = ft_list_new(envp[i]);
		ft_envlstadd_back(&root, new);
		i++;
	}
	return (root);
}