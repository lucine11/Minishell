#include "libft.h"

int	ft_putnbr(long n, int cnt, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		cnt++;
		n *= -1;
	}
	if (n >= 10)
	{
		cnt = ft_putnbr(n / 10, cnt, fd);
		cnt = ft_putnbr(n % 10, cnt, fd);
	}
	else
	{
		n += 48;
		write(fd, &n, 1);
		cnt++;
	}
	return (cnt);
}