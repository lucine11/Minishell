/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:28:26 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/01 17:58:20 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
 
void    ft_pwd(void)
{
    char *pwd;

    exit_status = 0;
    pwd = getcwd(0, 0);
    if (!pwd)
        return ;
    printf("%s\n", pwd);
    free(pwd);
}

