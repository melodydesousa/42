/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:42:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/06/23 15:38:59 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_format_arg(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\0' || s[i] == ' ')
	{
		write(2, "Error\n", 6);
		return (1);
	}
	while (s[i])
	{
		if ((s[i] >= '0' && s[i] <= '9') || (s[i] = '-'))
			i++;
		else
		{
			write(2, "Error\n", 6);
			return (1);
		}
	}
	return (0);
}

int	check_nb_arg(char **av)
{
	int i;
	
	i = 1;
	while (av[i])
	{
		if (check_format_arg(av[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int ft_atoi(char *s)
{
	long int n;
	int i;
	int count;

	i = 0;
	n = 0;
	count = 0;
	if (s[i] == '-')
	{
		count++;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = (n * 10) + (s[i] - 48);
		i++;
	}
	if (count == 1)
		n = -n;
	if (n >= 2147483648)
	{
		write (2, "Error\n", 6);
		return (0);
	}
	return (n);
}

int	check_doublon(t_stack stack)
{
	int	j;

	j = 0;
	while (j <= --stack.size)
	{
		
		while (stack.a[j] && j < stack.size)
		{
			if (stack.a[j] == stack.a[stack.size])
			{
				free(stack.a);
				write(2, "Error\n", 6);
				return (1);
			}
			j++;
		}
		j = 0;
	}
	return (0);
}

int	*ft_reverse_a(t_stack stack)
{
	int	j;
	int	tmp;

	j = 0;
	while (j < stack.size - 1)
	{
		tmp = stack.a[stack.size - 1];
		stack.a[stack.size - 1] = stack.a[j];
		stack.a[j] = tmp;
		j++;
		stack.size--;
	}
	return (stack.a);
}

// int	*ft_make_a_split(char **tab, int i)
// {
// 	int	*a;

// 	while (tab[i])
// 	{
// 		if (check_format_arg(tab[i]) == 1)
// 			return (0);
// 		i++;
// 	}
// 	a = malloc(sizeof(int) * i + 1);
// 	if (a == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (tab[i])
// 	{
// 		a[i] = ft_atoi(tab[i]);
// 		i++;
// 	}
// 	return (a);
// }

// int	*ft_make_a_arg(char **av, int i, int ac)
// {
// 	int	*a;
// 	int	j;

// 	j = 0;
// 	a = malloc(sizeof(int) * ac);
// 	while (av[i] && j < ac)
// 	{
// 	 	a[i] = ft_atoi(av[j]);
// 	 	i++;
// 	 	j++;
// 	}
// 	return (a);
// }

// int	count_arg(int *a)
// {
// 	int	i;
	
// 	i = 0;
// 	while (a[i])
// 		i++;
// 	return (i);
// }