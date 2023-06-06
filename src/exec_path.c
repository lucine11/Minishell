/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:04:45 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/06 01:19:37 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**split_path(t_env *env)
{
	char	**path;
	t_env	*ptr;

	ptr = env;
	while (ptr && ft_strcmp(ptr->name, "PATH"))
		ptr = ptr->next;
	path = NULL;
	if (ptr)
		path = ft_split(ptr->value, ':');
	return (path);
}

static char	*get_path(char *cmd, char **split_paths, int i, int acs)
{
	char	*path_of_cmd;

	if (!acs)
		return (ft_strdup(cmd));
	if (!split_paths)
	{
		perror(cmd);
		return (NULL);
	}
	cmd = ft_strjoin("/", cmd);
	while (split_paths && split_paths[i] && acs == -1)
	{
		path_of_cmd = ft_strjoin(split_paths[i++], cmd);
		acs = access(path_of_cmd, X_OK);
		if (acs == -1)
			free(path_of_cmd);
	}
	free(cmd);
	if (acs == -1)
		return (NULL);
	return (path_of_cmd);
}

char	*get_thepath(char **cmd_arg, int *tokens, t_env *env)
{
	char	*cmd;
	char	**paths;
	int		i;
	int		acs;

	i = 0;
	while (cmd_arg[i] && tokens[i] != COM_NAME && tokens[i] != COM_ARGUMENT)
		i++;
	if (!cmd_arg[i] || !cmd_arg[i][0])
		return (NULL);
	paths = split_path(env);
	acs = access(cmd_arg[i], X_OK);
	cmd = get_path(cmd_arg[i], paths, 0, acs);
	ft_free((void **)paths);
	return (cmd);
}