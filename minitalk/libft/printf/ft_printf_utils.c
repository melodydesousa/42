/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:50:07 by mede-sou          #+#    #+#             */
/*   Updated: 2022/06/06 11:19:45 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	i;

	i = count(n);
	if (n >= 0 && n < 10)
	{
		n = n + 48;
		write(1, &n, 1);
	}
	else if (n < 0 && n != -2147483648)
	{
		write(1, "-", 1);
		ft_putnbr(-n);
	}
	else if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	return (i);
}

int	count(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	if (n >= 0 && n < 10)
		count++;
	return (count);
}

int	ft_putnbr_u(unsigned int n)
{
	int			i;
	long int	nbr;

	nbr = n;
	i = count(n);
	if (nbr >= 0 && nbr < 10)
	{
		nbr = nbr + 48;
		write(1, &nbr, 1);
	}
	else
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	return (i);
}

int	hexa(unsigned int nbr, char *base)
{
	int	i;

	i = count_hexa(nbr);
	if (nbr <= 15)
	{
		write(1, &base[nbr], 1);
	}
	else
	{
		hexa(nbr / 16, base);
		hexa(nbr % 16, base);
	}
	return (i);
}

int	count_hexa(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 15)
	{
		n = n / 16;
		count++;
	}
	if (n >= 0 && n <= 16)
		count++;
	return (count);
}
