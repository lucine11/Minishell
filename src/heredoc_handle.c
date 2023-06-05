/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 01:36:42 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/04 06:56:50 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Returns 0 on failure and 1 on success.
int handle_single_heredoc(char *limit)
{
    char *line;
    int fd[2];
    
    if(pipe(fd) == -1)
    {
        perror("pipe");
        return 0;
    }

    while(1)
    {
        line = readline("heredoc> ");
        if(line == NULL) 
        {
            fprintf(stderr, "Unexpected EOF while reading heredoc\n");
            close(fd[0]);
            close(fd[1]);
            free(line);
            return 0;
        }
        if(ft_strcmp(line, limit) == 0) 
        {
            free(line);
            break;
        }
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    
    if(dup2(fd[0], STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd[0]);
        return 0;
    }
    close(fd[0]);
    return 1;
}
int heredoc_handler(t_command *command) 
{
    char *limit;
    int i, j;

    for(i = 0; i < command->com_count; i++) 
    {
        for(j = 0; command->command_segments[i][j] != NULL; j++) 
        {
            if(command->token_types[i][j] == HER_LIMITER) 
            {
                limit = command->command_segments[i][j+1];
                if(limit == NULL) 
                {
                    fprintf(stderr, "Error: No heredoc limit string.\n");
                    return 1;
                }
                if(!handle_single_heredoc(limit))
                {
                    fprintf(stderr, "Error: Failed to handle heredoc.\n");
                    return 1;
                }
            }
        }
    }
    return 0;
}