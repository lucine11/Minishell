/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 12:58:36 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/13 13:00:00 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	check_for_pipe(char c)
{
	if (c == '|')
		return (true);
	return (false);
}

bool	check_for_redirection(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

bool	check_for_space(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}