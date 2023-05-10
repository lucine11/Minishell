#include "libft.h"

int	ft_putptr(unsigned long ptr, int fd)
{
	if (!ptr)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	write(fd, "0x", 2);
	return (ft_puthex(ptr, 1, 2, fd));
}