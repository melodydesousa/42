/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:04:01 by mede-sou          #+#    #+#             */
/*   Updated: 2022/06/06 11:21:11 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		ft_count_putchar(char c);
int		ft_check_ptr(va_list list, char c);
int		ft_ptr(unsigned long long n, char *base);
int		count_ptr(unsigned long long int n);
int		check_format(va_list list, char c, int nb_printed);
int		ft_count_putstr(char *s);
int		ft_putnbr(int n);
int		count(long int n);
int		ft_putnbr_u(unsigned int n);
int		hexa(unsigned int n, char *base);
int		count_hexa(long int n);

#endif