/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:44:36 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/01 01:43:53 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	
	while(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{	
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}


void    ft_echo(char **arg)
{
	int x;

	x = 0;
	if (ft_strcmp(arg[1], "-n"))
	{
		x = 1;
		arg++;	
	}
    arg++;
    while (*arg)
    {
        ft_putstr_fd(*arg, 1);
		if (*(arg + 1) != NULL)
			write (1, " ", 1);
        arg++;
    }
	if (x == 0)
	{
		write (1, "\n", 1);	
	}
}
// int main(int ac, char **av)
// {
//     (void)ac;
//     ft_echo(av);
// }