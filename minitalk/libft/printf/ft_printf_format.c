/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:07:39 by mede-sou          #+#    #+#             */
/*   Updated: 2022/06/06 11:22:02 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_ptr(va_list list, char c)
{
	int					nb_printed;
	unsigned long long	tmp;

	nb_printed = 0;
	nb_printed += check_format(list, c, nb_printed);
	if (c == 'p')
	{
		tmp = (unsigned long long)va_arg(list, void *);
		if (tmp == 0)
		{
			write(1, "(nil)", 5);
			nb_printed += 5;
		}
		else
		{
			write(1, "0x", 2);
			nb_printed += ft_ptr(tmp, "0123456789abcdef") + 2;
		}
	}
	return (nb_printed);
}

int	check_format(va_list list, char c, int nb_printed)
{
	if (c == 'c')
		nb_printed += ft_count_putchar(va_arg(list, int));
	if (c == '%')
	{
		nb_printed++;
		write(1, &c, 1);
	}
	if (c == 's')
		nb_printed += ft_count_putstr(va_arg(list, char *));
	if (c == 'd' || c == 'i')
		nb_printed += ft_putnbr(va_arg(list, int));
	if (c == 'u')
		nb_printed += ft_putnbr_u(va_arg(list, unsigned int));
	if (c == 'x')
		nb_printed += hexa(va_arg(list, unsigned int), "0123456789abcdef");
	if (c == 'X')
		nb_printed += hexa(va_arg(list, unsigned int), "0123456789ABCDEF");
	return (nb_printed);
}

int	ft_ptr(unsigned long long int nbr, char *base)
{
	int	i;

	i = count_ptr(nbr);
	if (nbr <= 15)
		write(1, &base[nbr], 1);
	else
	{
		ft_ptr(nbr / 16, base);
		ft_ptr(nbr % 16, base);
	}
	return (i);
}

int	count_ptr(unsigned long long int n)
{
	int	count;

	count = 0;
	while (n > 15)
	{
		n = n / 16;
		count++;
	}
	if (n <= 16)
		count++;
	return (count);
}
