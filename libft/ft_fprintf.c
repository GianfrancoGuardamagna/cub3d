#include "libft.h"

int	ft_fprint_char(int fd, int c)
{
	return (write(fd, &c, 1));
}

int	ft_fprint_hex_bottom(int fd, unsigned long long num)
{
	unsigned int		printed_bytes;
	unsigned long long	d;

	printed_bytes = 0;
	d = num;
	if (num >= 16)
		printed_bytes += ft_fprint_hex_bottom(fd, d / 16);
	d = num % 16;
	if (d > 0 && d <= 9)
	{
		d = d + '0';
		printed_bytes += write(fd, &d, 1);
	}
	else if (d >= 10 && d < 16)
	{
		d = 'a' + (d - 10);
		printed_bytes += write(fd, &d, 1);
	}
	return (printed_bytes);
}

int	ft_fprint_hex_top(int fd, unsigned int num)
{
	unsigned int		printed_bytes;
	unsigned long long	d;

	printed_bytes = 0;
	d = (unsigned long long)num;
	if (num >= 16)
	{
		printed_bytes += ft_fprint_hex_top(fd, num / 16);
	}
	d = num % 16;
	if (d > 0 && d <= 9)
	{
		d = d + '0';
		printed_bytes += write(fd, &d, 1);
	}
	else if (d >= 10 && d < 16)
	{
		d = 'A' + (d - 10);
		printed_bytes += write(fd, &d, 1);
	}
	return (printed_bytes);
}

int	ft_fprint_specifier(int fd, char specifier, va_list input)
{
	int	printed_bytes;

	printed_bytes = 0;
	if (specifier == 'c')
		printed_bytes += ft_fprint_char(fd, va_arg(input, int));
	else if (specifier == 's')
		printed_bytes += ft_fprint_str(fd, va_arg(input, char *));
	else if (specifier == 'i')
		printed_bytes += ft_fprint_nbr(fd, va_arg(input, int));
	else if (specifier == 'd')
		printed_bytes += ft_fprint_nbr(fd, va_arg(input, int));
	else if (specifier == 'u')
		printed_bytes += ft_fprint_uns(fd, va_arg(input, unsigned int));
	else if (specifier == '%')
		printed_bytes += ft_fprint_char(fd, '%');
	else if (specifier == 'X')
		printed_bytes += ft_fprint_hex_top(fd, va_arg(input, unsigned int));
	else if (specifier == 'x')
		printed_bytes += ft_fprint_hex_bottom(fd, va_arg(input, unsigned int));
	else if (specifier == 'p')
		printed_bytes += ft_fprint_ptr(fd, va_arg(input, void *));
	return (printed_bytes);
}

int	ft_fprintf(int fd, char const *chain, ...)
{
	va_list	input;
	int		printed_bytes;
	int		i;

	va_start(input, chain);
	printed_bytes = 0;
	i = 0;
	while (chain[i] != '\0')
	{
		if (chain[i] == '%')
		{
			i++;
			printed_bytes += ft_fprint_specifier(fd, chain[i], input);
		}
		else
		{
			ft_fprint_char(fd, chain[i]);
			printed_bytes++;
		}
		i++;
	}
	va_end(input);
	return (printed_bytes);
}
