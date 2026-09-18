#include "libft.h"

int	ft_fprint_nbr(int fd, int num)
{
	char	d;
	int		printed_bytes;

	printed_bytes = 0;
	d = num;
	if (num == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (num < 0)
	{
		printed_bytes += write(fd, "-", 1);
		num *= -1;
	}
	if (num >= 10)
	{
		printed_bytes += ft_fprint_nbr(fd, num / 10);
	}
	d = num % 10 + '0';
	printed_bytes += write(fd, &d, 1);
	return (printed_bytes);
}

int	ft_fprint_ptr(int fd, void *ptr)
{
	unsigned long long int	cst;
	int						printed_bytes;

	printed_bytes = 0;
	cst = (unsigned long long int)ptr;
	if (!cst)
		printed_bytes += write(fd, "(nil)", 5);
	else
	{
		printed_bytes += write(fd, "0x", 2);
		printed_bytes += ft_fprint_hex_bottom(fd, cst);
	}
	return (printed_bytes);
}

int	ft_fprint_str(int fd, char *str)
{
	int	i;

	if (str == NULL)
	{
		(write(fd, "(null)", 6));
		return (6);
	}
	i = 0;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_fprint_uns(int fd, unsigned int num)
{
	int					printed_bytes;
	char				d;
	unsigned long int	n;

	n = num;
	printed_bytes = 0;
	if (n >= 10)
	{
		printed_bytes += ft_fprint_nbr(fd, n / 10);
	}
	d = n % 10 + '0';
	printed_bytes += write(fd, &d, 1);
	return (printed_bytes);
}
