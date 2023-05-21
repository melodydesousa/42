/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:58:50 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/24 12:29:49 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int	j;

	j = 0;
	data->mutex_forks = malloc(sizeof(pthread_mutex_t)
			* (data->number_of_philo + 1));
	if (data->mutex_forks == NULL)
		return ;
	while (j < data->number_of_philo)
	{
		pthread_mutex_init(&data->mutex_forks[j], NULL);
		j++;
	}
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_death, NULL);
}

int	init_arg(t_data *data, char **av)
{
	data->x_must_eat = 0;
	data->death = 0;
	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		data->x_must_eat = ft_atoi(av[5]);
		if (data->x_must_eat == 0)
			data->x_must_eat = -1;
		else
			data->check_x_must_eat = data->x_must_eat;
	}
	if (data->number_of_philo == -1 || data->number_of_philo == 0
		|| data->time_to_die == -1 || data->time_to_eat == -1
		|| data->time_to_sleep == -1 || data->x_must_eat == -1)
	{
		printf("Error\nInvalid argument\n");
		return (1);
	}
	init_mutex(data);
	if (data->mutex_forks == NULL)
		return (1);
	return (0);
}

void	init_philo(t_philo *philo, t_data *data, int j)
{
	philo[j].data = data;
	philo[j].i = j;
	philo[j].ate = 0;
	philo[j].last_meal = 0;
}
