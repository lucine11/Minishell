/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:44:48 by codespace         #+#    #+#             */
/*   Updated: 2023/05/22 14:07:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*insert_spaces_around_operators(char *cmd)
{
	int		i;
	int		state;
	char	*new_cmd;

	i = 0;
	state = 0;
	new_cmd = ft_strdup(cmd);
	free (cmd);
	while (new_cmd[i])
	{
		change_value_state(&state, new_cmd[i]);
		if (state == 0 && (is_redirection(new_cmd[i]) || is_pipe(new_cmd[i])))
		{
			if (i > 1 && ft_strlen(new_cmd) > 1
				&& !is_space(new_cmd[i - 1]) && !is_redirection(new_cmd[i - 1]))
				new_cmd = insert_space_before_operator(new_cmd, i);
		}
		i++;
	}
	new_cmd = insert_spaces_after_operators(new_cmd);
	return (new_cmd);
}

static char	*insert_spaces_after_operators(char *cmd)
{
	char	*new_cmd;
	int		i;
	int		state;
	int		operator_length;

	i = -1;
	operator_length = 0;
	state = 0;
	new_cmd = ft_strdup(cmd);
	free (cmd);
	while (new_cmd[++i])
	{	
		change_value_state(&state, new_cmd[i]);
		if (state == 0 && (is_redirection(new_cmd[i]) || is_pipe(new_cmd[i])))
		{
			if (is_redirection(new_cmd[i]))
				operator_length += 1;
			new_cmd = ensure_space_after_operator(new_cmd, i, &operator_length);
		}
	}
	return (new_cmd);
}

static char	*ensure_space_after_operator(char *new_cmd, int i, int *operator_length)
{
	if ((new_cmd[i + 1] && !is_space(new_cmd[i + 1])
			&& !is_redirection(new_cmd[i + 1])) || *operator_length == 2)
	{
		new_cmd = insert_space_after_operator(new_cmd, i);
		*operator_length = 0;
	}
	else
		*operator_length = 0;
	return (new_cmd);
}

char	*add_space_before_operator(char *str, int i)
{
	char	*new_str;
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, i);
	tmp2 = ft_strjoin(tmp, " ");
	free (tmp);
	tmp = ft_substr(str, i, ft_strlen(str) - i);
	new_str = ft_strjoin(tmp2, tmp);
	free (tmp);
	free (tmp2);
	free (str);
	return (new_str);
}

static char	*add_space_after_operator(char *str, int i)
{
	char	*new_str;
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, i + 1);
	tmp2 = ft_strjoin(tmp, " ");
	free (tmp);
	tmp = ft_substr(str, i + 1, ft_strlen(str) - (i + 1));
	new_str = ft_strjoin(tmp2, tmp);
	free (tmp);
	free (tmp2);
	free (str);
	return (new_str);
}
