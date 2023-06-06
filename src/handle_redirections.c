/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:39:14 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/06 08:09:49 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_outfile(char *filename, int mode)
{
	int	fd;
	int	open_mode;

	open_mode = O_TRUNC;
	if (mode == APPEND_O_FILE)
		open_mode = O_APPEND;
	fd = open(filename, O_WRONLY | O_CREAT | open_mode, 0644);
	if (fd == -1)
	{
		ft_printf(2, "minishell: ");
		perror(filename);
	}
	return (fd);
}

static int	open_infile(char *filename, int mode)
{
	int	fd;

	if (mode == HER_LIMITER)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "minishell: ");
		perror(filename);
	}
	return (fd);
}

static void	file_finder(t_command *exec, int cmd_nb, int pipeline[2][2], int i)
{
	int	fds[2];

	fds[0] = pipeline[(cmd_nb + 1) % 2][0];
	fds[1] = pipeline[cmd_nb % 2][1];
	while (exec->command_segments[cmd_nb][++i] && fds[0] != -1 && fds[1] != -1)
	{
		if (exec->token_types[cmd_nb][i] == RED_OUTPUT_FILE
			|| exec->token_types[cmd_nb][i] == APPEND_O_FILE)
		{
			close_fd(fds[1]);
			fds[1] = open_outfile(exec->command_segments[cmd_nb][i], exec->token_types[cmd_nb][i]);
		}
		else if (exec->token_types[cmd_nb][i] == RED_INPUT_FILE)
		{
			close_fd(fds[0]);
			fds[0] = open_infile(exec->command_segments[cmd_nb][i], exec->token_types[cmd_nb][i]);
		}
	}
	// if (fds[0] != -1 && fds[1] != -1)
	// 	fds[0] = check_heredoc_use(fds[0], exec, cmd_nb);
	// else
	// 	close_unused_hd(exec->heredoc, cmd_nb);
	// pipeline[(cmd_nb + 1) % 2][0] = fds[0];
	// pipeline[cmd_nb % 2][1] = fds[1];
}

void	handle_redirections(t_command *exec, int cmd_nb)
{
	if (exec->com_count == 1 && cmd_nb == 0)
	{
		exec->pipeline[1][0] = dup(0);
		exec->pipeline[0][1] = dup(1);
		file_finder(exec, cmd_nb, exec->pipeline, -1);
		return ;
	}
	if (cmd_nb == 0)
	{
		pipe(exec->pipeline[0]);
		exec->pipeline[1][0] = dup(0);
		file_finder(exec, cmd_nb, exec->pipeline, -1);
		return ;
	}
	if (cmd_nb == exec->com_count - 1)
	{
		exec->pipeline[cmd_nb % 2][1] = dup(1);
		file_finder(exec, cmd_nb, exec->pipeline, -1);
		return ;
	}
	pipe(exec->pipeline[cmd_nb % 2]);
	file_finder(exec, cmd_nb, exec->pipeline, -1);
}
// static void	close_unused_hd(int heredoc_fd[16][2], int cmd_nb)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 16)
// 	{
// 		if (heredoc_fd[i][0] == cmd_nb)
// 			close(heredoc_fd[i][1]);
// 		i++;
// 	}
// }
