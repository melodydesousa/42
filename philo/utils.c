/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:54:43 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/05 16:20:37 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_str_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '\0')
	{
		while (str[i] != '\0')
		{
			if (str[i] > 47 && str[i] < 58)
				i++;
			else
				return (0);
		}
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (ft_str_is_numeric((char *)(nptr + i)) == 0)
	{
		printf("Error\n");
		return (-1);
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + (nptr[i] - 48);
		i++;
	}
	return (n);
}

long long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec ) / 1000);
}

long long	time_diff(t_data data)
{
	return (timestamp() - data.first_time);
}