/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:44:36 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/02 15:57:17 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		check_for_n(char *cmd)
{
	int x;

	x = 1;
	if (!cmd)
		return (0);
	while (cmd[x])
	{
		if (cmd[0] != '-')
			return (0);
		if (cmd[x] != 'n')
			return (0);
		x++;
	}
	return (1);
	
}

void    ft_echo(char **cmd, int *tok)
{
	int x;

	x = 0;
    cmd++;
	(void)tok;
	if (cmd[0] && ft_strncmp(cmd[0], "-n", 2) == 0)
	{
		x = 1;
		cmd++;
		while (check_for_n(*cmd))
			cmd++;
	}
    while (*cmd)
    {
        ft_putstr_fd(*cmd, 1);
		if (*(cmd + 1) != NULL)
			write (1, " ", 1);
        cmd++;
    }
	if (x == 0)
	{
		write (1, "\n", 1);	
	}
}
//
//
