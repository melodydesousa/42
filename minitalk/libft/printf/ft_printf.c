/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:10:31 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 13:11:02 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		nb_printed;
	int		i;
	va_list	list;

	i = 0;
	nb_printed = 0;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			nb_printed += ft_check_ptr(list, str[i + 1]);
			i++;
		}
		else
			nb_printed += ft_count_putchar(str[i]);
		i++;
	}
	va_end(list);
	return (nb_printed);
}

int	ft_count_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_count_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == 0)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

// #include <stdio.h>
// #include <limits.h>
// int main ()
// {
// 	//char b = 'c';
// 	// char *s = NULL;
// 	//char *ptr = &b;
// 	// ft_printf("%d\n", (ft_printf("caractere = %c\n", b)));
// 	// printf("%d\n", (printf("caractere = %c\n", b)));
// 	// printf("--------------------------------\n");
// 	// ft_printf("%d\n", (ft_printf("pourcent = %%\n")));
// 	// printf("%d\n", (printf("pourcent = %%\n")));
// 	// printf("--------------------------------\n");
// 	// ft_printf("%d\n", (ft_printf("string = %s\n", s)));
// 	// printf("%d\n", (printf("string = %s\n", s)));
// 	printf("--------------------------------\n");
// 	ft_printf("%d\n", (ft_printf("pointeur = %p\n", (void *)16)));
// 	printf("%d\n", (printf("pointeur = %p\n", (void *)16)));
// 	printf("--------------------------------\n");
// 	// // ft_printf("%d\n", (ft_printf("int d = %d\n", 551)));
// 	// printf("%d\n", (printf("int d = %d\n", 551)));
// 	// printf("--------------------------------\n");
// 	// ft_printf("%d\n", (ft_printf("int i = %i\n", 42)));
// 	// printf("%d\n", (printf("int i = %i\n", 42)));
// 	// printf("--------------------------------\n");
// 	// printf("%d\n", (printf("unsigned int = %u %%\n", INT_MIN)));
// 	printf("--------------------------------\n");
// 	ft_printf("%d\n", (ft_printf("hexa x = %x\n", 16)));
// 	printf("%d\n", (printf("hexa x = %x\n", 16)));
// 	printf("--------------------------------\n");
// 	ft_printf("%d\n", (ft_printf("hexa X = %X\n", 16)));
// 	printf("%d\n", (printf("hexa X = %X\n", 16)));
// 	return (0);
// }