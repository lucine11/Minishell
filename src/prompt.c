/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:17:42 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/25 18:51:06 by lahamoun         ###   ########.fr       */
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

static void	prompt_get_exitc(int exit)
{
	if (exit == 0)
		return ;
	printf("[%d]", exit);
}

static void	prompt_get_path(t_env *env)
{
	t_env	*home;
	char	*pwd;
	char	*tmp;
	int		home_length;

	pwd = getcwd(NULL, 4096);
	home = ft_lst_search(env, "HOME");
	if (home && ft_strlen(home->value) > 0)
	{
		home_length = ft_strlen(home->value);
		if (ft_strncmp(pwd, home->value, home_length) == 0)
		{
			tmp = ft_substr(pwd, home_length, ft_strlen(pwd) - home_length);
			printf("[~%s]", tmp);
			free(pwd);
			free(tmp);
			return ;
		}
	}
	printf("[%s]", pwd);
	free(pwd);
}

static void	prompt_get_user(t_env *env)
{
	t_env		*env_tmp;

	env_tmp = ft_lst_search(env, "USER");
	if (!env_tmp)
		return ;
	if (env_tmp->value)
		printf("%s@", env_tmp->value);
	// env_tmp = ft_lst_search(env, "SESSION_MANAGER");
	// if (!env_tmp)
	// 	return ;
	// tmp = ft_substr(env_tmp->value, 6, 3);
	// if (tmp)
	// 	printf("%s:", tmp);
	// free(tmp);
}

void	get_prompt(t_env *env)
{
	prompt_get_user(env);
	prompt_get_path(env);
	prompt_get_exitc(exit_status);
	printf("\n");
}