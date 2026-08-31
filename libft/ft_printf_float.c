/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-03 18:55:23 by jmagand           #+#    #+#             */
/*   Updated: 2025-02-03 18:55:23 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_handle_precision(int *count, int precision, double frac_part,
	int fd)
{
	int	digit;
	int	i;

	digit = 0;
	if (precision > 0)
	{
		*count += write(fd, ".", fd);
		i = 0;
		while (i < precision && i < 15)
		{
			frac_part *= 10;
			digit = (int)frac_part;
			*count += ft_putchar(digit + '0', fd);
			frac_part -= digit;
			i++;
		}
	}
}

int	ft_putnbr_float(double n, int precision, int fd)
{
	int			count;
	long long	int_part;
	double		frac_part;

	count = 0;
	if (n < 0)
	{
		count += write(fd, "-", 1);
		n = -n;
	}
	int_part = (long long)n;
	frac_part = n - int_part;
	count += ft_putnbr(int_part, fd);
	if (precision == -1)
		precision = 6;
	ft_handle_precision(&count, precision, frac_part, fd);
	return (count);
}
