/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-21 17:12:13 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-21 17:12:13 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_precision(const char *format, size_t *i)
{
	int	precision;

	precision = -1;
	if (format[*i] == '.')
	{
		(*i)++;
		precision = 0;
		while (format[*i] >= '0' && format[*i] <= '9')
		{
			precision = precision * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
	return (precision);
}

static int	ft_printf_args(va_list args, const char *format, size_t *i)
{
	int	precision;

	precision = ft_get_precision(format, i);
	if (format[*i] == 'c')
		return (ft_putchar(va_arg(args, int), 1));
	else if (format[*i] == 's')
		return (ft_putstr(va_arg(args, char *), 1));
	else if (format[*i] == 'i' || format[*i] == 'd')
		return (ft_putnbr(va_arg(args, int), 1));
	else if (format[*i] == 'u')
		return (ft_putnbr_u(va_arg(args, unsigned int)));
	else if (format[*i] == 'p')
		return (ft_putadress(va_arg(args, void *),
				"0123456789abcdef"));
	else if (format[*i] == 'x')
		return (ft_putnbr_hex(va_arg(args, unsigned int),
				"0123456789abcdef"));
	else if (format[*i] == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int),
				"0123456789ABCDEF"));
	else if (format[*i] == '%')
		return (ft_putchar('%', 1));
	else if (format[*i] == 'f')
		return (ft_putnbr_float(va_arg(args, double), precision, 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		count;

	if (!format)
		return (-1);
	va_start (args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_printf_args(args, format, &i);
		}
		else
			count += ft_putchar(format[i], 1);
		i++;
	}
	va_end (args);
	return (count);
}

// int	main()
// {
// 	#include <stdio.h>

// 	char *str;
// 	str = NULL;
// 	printf("True = %i\n\n", printf("\nC'quoi les bails : %p\n", str));
// 	ft_printf("FT = %i\n", ft_printf("\nC'quoi les bails : %p\n", str));
// 	return (0);
// }
