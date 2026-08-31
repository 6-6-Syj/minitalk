/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-21 19:32:20 by jmagand           #+#    #+#             */
/*   Updated: 2024-11-21 19:32:20 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	int_len(long nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	if (nb == 0)
		count++;
	while (nb != 0)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}

int	ft_putnbr(int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "21", 2);
		write(fd, "47483648", 8);
		return (11);
	}
	if (n < 0)
	{
		n *= -1;
		count = ft_putchar('-', 1);
	}
	if (n > 9)
		ft_putnbr(n / 10, 1);
	ft_putchar(n % 10 + 48, 1);
	return (int_len(n) + count);
}

int	ft_putnbr_u(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		ft_putnbr(n / 10, 1);
	ft_putchar(n % 10 + 48, 1);
	return (int_len(n) + count);
}

int	base_len(char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
		i++;
	return (i);
}

int	ft_putnbr_base_ul(unsigned long long nbr, char *base)
{
	int	count;

	count = 0;
	if (nbr >= (unsigned long long) base_len(base))
		count += ft_putnbr_base_ul(nbr / base_len(base), base);
	count += write(1, &base[nbr % base_len(base)], 1);
	return (count);
}
