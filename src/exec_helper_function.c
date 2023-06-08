/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:58:19 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/07 08:55:03 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**transform_envp(t_env *env)
{
	int		i;
	char	*tmp;
	char	**env_array;

	env_array = malloc(sizeof(char *) * (ft_list_size(env) + 1));
	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->name, "=");
			env_array[i] = ft_strjoin(tmp, env->value);
			free (tmp);
		}
		else
			env_array[i] = ft_strdup(env->name);
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
