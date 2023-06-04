/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:39:14 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/04 01:15:57 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void handle_redirections(t_command *command) 
{
    int j = 0;
    while (command->command_segments[j]) 
    {
        char **segment = command->command_segments[j];
        int i = 0;
        while (segment[i]) 
        {
            if (command->token_types[j][i] == RED_INPUT_SIGNAL) 
            {
                int fd = open(segment[i+1], O_RDONLY);
                if (fd == -1) 
                {
                    ft_printf(2,"open");
                    return;
                }
                if (dup2(fd, 0) == -1) 
                {
                    ft_printf(2, "dup2");
                    return;
                }
                close(fd);
            }
            else if (command->token_types[j][i] == RED_OUTPUT_SIGNAL) 
            {
                int fd = open(segment[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    ft_printf(2, "open");
                    return;
                }
                if (dup2(fd, 1) == -1) 
                {
                    ft_printf(2, "dup2");
                    return;
                }
                close(fd);
            }
            else if (command->token_types[j][i] == APPEND_O_SIGNAL) 
            {
                int fd = open(segment[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd == -1) 
                {
                    ft_printf(2, "open");
                    return;
                }
                if (dup2(fd, 1) == -1) 
                {
                    ft_printf(2, "dup2");
                    return;
                }
                close(fd);
            }
            else if (command->token_types[j][i] == HER_SIGNAL) 
            {
                char *temp_file_name = "/tmp/heredoc_temp";
                int fd = open(temp_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) 
                {
                    ft_printf(2, "open");
                    return;
                }
                write(fd, segment[i+1], ft_strlen(segment[i+1]));
                close(fd);

                fd = open(temp_file_name, O_RDONLY);
                if (fd == -1) 
                {
                    ft_printf(2, "open");
                    return;
                }
                if (dup2(fd, 0) == -1) 
                {
                    ft_printf(2, "dup2");
                    return;
                }
                close(fd);

                if (remove(temp_file_name) == -1) 
                {
                    ft_printf(2, "remove");
                    return;
                }
            }
            i++;
        }
        j++;
    }
}
