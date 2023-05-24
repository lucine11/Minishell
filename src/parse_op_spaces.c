/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:06:57 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/24 16:07:00 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*insert_space_before_operator(char *str, int i)
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

char	*insert_space_after_operator(char *str, int i)
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

char	*ensure_space_after_operator(char *new_cmd, int i, int *op_length)
{
	if ((new_cmd[i + 1] && !check_for_space(new_cmd[i + 1])
			&& !check_for_redirection(new_cmd[i + 1])) || *op_length == 2)
	{
		new_cmd = insert_space_after_operator(new_cmd, i);
		*op_length = 0;
	}
	else
		*op_length = 0;
	return (new_cmd);
}

char	*parse_after_operators(char *cmd)
{
	char	*new_cmd;
	int		i;
	int		state;
	int		op_length;

	i = -1;
	op_length = 0;
	state = 0;
	new_cmd = ft_strdup(cmd);
	free (cmd);
	while (new_cmd[++i])
	{	
		change_value_state(&state, new_cmd[i]);
		if (state == 0 && (check_for_redirection(new_cmd[i]) || check_for_pipe(new_cmd[i])))
		{
			if (check_for_redirection(new_cmd[i]))
				op_length += 1;
			new_cmd = ensure_space_after_operator(new_cmd, i, &op_length);
		}
	}
	return (new_cmd);
}

char	*parse_op(char *cmd)
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
		if (state == 0 && (check_for_redirection(new_cmd[i]) || check_for_pipe(new_cmd[i])))
		{
			if (i > 1 && ft_strlen(new_cmd) > 1
				&& !check_for_space(new_cmd[i - 1]) && !check_for_redirection(new_cmd[i - 1]))
				new_cmd = insert_space_before_operator(new_cmd, i);
		}
		i++;
	}
	new_cmd = parse_after_operators(new_cmd);
	return (new_cmd);
}
