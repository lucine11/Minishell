/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bultin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:19:59 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/02 15:19:52 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool execute_builtin(char **cmds, int *toks, t_env *env)
{
    int	i;
    (void)env;

    i = 0;
    // while (cmds[++i])
    //     printf("%s\n%d\n\n\n", cmds[i], toks[i]);
    // while (env)
    // {
    //     printf("%s=%s\n", env->name, env->value);
    //     env = env->next;
    // }        
    while (cmds && cmds[i] && toks && toks[i] != COM_NAME && toks[i] != COM_ARGUMENT)
        i++;
    if (!cmds[i])
        return false;

    if (!ft_strcmp(cmds[i], "pwd"))
    {
       ft_pwd();
    }
    else if (!ft_strcmp(cmds[i], "env"))
    {
        //
    }
    else if (!ft_strcmp(cmds[i], "echo"))
    {
        ft_echo(cmds, toks);
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
