/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 09:39:42 by mede-sou          #+#    #+#             */
/*   Updated: 2022/02/17 10:46:35 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	result;

	result = 1;
	if (nb == 0)
		return (1);
	if (power < 0)
		return (0);
	while (power > 0)
	{	
		result = result * nb;
		power--;
	}
	return (result);
}
/*
#include <stdio.h>

int ft_iterative_power(int nb, int power);

int	main(void)
{
	printf("0:%d\n", ft_iterative_power(-77, -4128));
	printf("1:%d\n", ft_iterative_power(0, 0));
	printf("1:%d\n", ft_iterative_power(1087, 0));
	printf("3041:%d\n", ft_iterative_power(3041, 1));
	printf("4:%d\n", ft_iterative_power(2, 2));
	printf("125:%d\n", ft_iterative_power(5, 3));
	printf("1296:%d\n", ft_iterative_power(6, 4));
	printf("-16807:%d\n", ft_iterative_power(-7, 5));
	printf("1679616:%d\n", ft_iterative_power(-6, 8));
	printf("-1953125:%d\n", ft_iterative_power(-5, 9));
	printf("1:%d\n", ft_iterative_power(-1, 10));
}
*/
