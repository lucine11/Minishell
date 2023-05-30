/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_unctionss.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 02:16:05 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/30 17:48:11 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin_many(int num_args, ...)
{
	va_list	ap;
	char	*res;
	char	*temp;
	char	*arg;
	int 	i;

	va_start(ap, num_args);
	res = ft_strdup("");  // Start with an empty string
	for (i = 0; i < num_args; i++)
	{
		arg = va_arg(ap, char*);
		temp = ft_strjoin(res, arg); // Join current string and next argument
		free(res); // Free old string
		res = temp; // Update string
	}
	va_end(ap);
	return (res);
}

#include <stdlib.h>

char *ft_strjoin_char(const char *s1, const char *s2, char c)
{
    size_t len_s1 = 0;
    size_t len_s2 = 0;
    size_t i = 0;
    char *new_str;

    if (!s1 || !s2)
        return NULL;

    while (s1[len_s1])
        len_s1++;

    while (s2[len_s2])
        len_s2++;

    new_str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 2));
    if (!new_str)
        return NULL;

    while (*s1)
        new_str[i++] = *s1++;

    new_str[i++] = c;

    while (*s2)
        new_str[i++] = *s2++;

    new_str[i] = '\0';

    return new_str;
}
