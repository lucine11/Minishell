/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bultin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:19:59 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/03 03:32:50 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool execute_builtin(char **cmds, int *toks, t_env *env)
{
    int	i;
    (void)env;

    i = 0;      
    while (cmds && cmds[i] && toks && toks[i] != COM_NAME && toks[i] != COM_ARGUMENT)
        i++;
    if (!cmds[i])
        return false;

    if (!ft_strcmp(cmds[i], "pwd"))
    {
       ft_pwd();
       return (true);
    }
    else if (!ft_strcmp(cmds[i], "env"))
    {
        //
    }
    else if (!ft_strcmp(cmds[i], "echo"))
    {
        ft_echo(cmds, toks);
        return true;
    }
    else if (!ft_strcmp(cmds[i], "cd"))
    {
        //
    }
    else if (!ft_strcmp(cmds[i], "export"))
    {
        //
    }
    else if (!ft_strcmp(cmds[i], "unset"))
    {
        //
    }
    else if (!ft_strcmp(cmds[i], "exit"))
    {
        //
    }
    else
    {
        return false;
    }

    return false;
}
