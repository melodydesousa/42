/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:57:45 by mede-sou          #+#    #+#             */
/*   Updated: 2022/09/29 11:42:12 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_make_str(char *str, char c)
{
	int		i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
		i++;
	str[i] = c;
	str[i + 1] = '\0';
}

char	binary_to_char(char *str)
{
	int		i;
	int		j;
	int		res;

	i = 0;
	j = 6;
	res = 0;
	while (i < 7)
	{
		res = res + ((str[i] - 48) * ft_iterative_power(2, j));
		i++;
		j--;
	}
	return (res);
}

char	*ft_make_stock(char *stock_str, char c)
{
	char	*new_stock;
	int		i;

	i = 0;
	new_stock = malloc (ft_strlen_gnl(stock_str) + 2);
	if (new_stock == NULL)
		return (NULL);
	while (stock_str && stock_str[i])
	{
		new_stock[i] = stock_str[i];
		i++;
	}
	new_stock[i] = c;
	new_stock[i + 1] = '\0';
	return (new_stock);
}

void	make_c(int signum, char *str, char *stock_str)
{	
	if (signum == SIGUSR1)
		ft_make_str(str, '0');
	else if (signum == SIGUSR2)
		ft_make_str(str, '1');
	else if (signum == SIGINT)
	{
		if (stock_str)
			free(stock_str);
		exit (0);
	}
	else
	{
		ft_printf("Error: unknown signal\n");
		if (stock_str)
			free(stock_str);
		exit (0);
	}
}
