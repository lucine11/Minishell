/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:24:28 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/24 16:44:49 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*get_env_variables(char **envp)
{
	int		i;
	t_env	*root;
	t_env	*new;

	i = 0;
	root = NULL;
	while (envp[i])
	{
		new = ft_envlst_new(envp[i]);
		ft_envlstadd_back(&root, new);
		i++;
	}
	return (root);
}