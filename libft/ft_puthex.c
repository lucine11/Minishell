/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:42:31 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/10 15:42:33 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned long n, int lowcase, int cnt, int fd)
{
	char		to_wrt;
	char		*base;

	base = "0123456789abcdef";
	if (!lowcase)
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		cnt += ft_puthex(n / 16, lowcase, 0, fd);
		cnt += ft_puthex(n % 16, lowcase, 0, fd);
	}
	else
	{
		to_wrt = base[n];
		write(fd, &to_wrt, 1);
		cnt++;
	}
	return (cnt);
}