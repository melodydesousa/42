/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_sleep_think.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:52:47 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/25 12:21:29 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	if (check_death(philo) == 0 && mutex_check_death(philo) == 0)
	{
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%lld %d is sleeping\n", t_diff(philo->data->t_time),
			philo->i + 1);
		pthread_mutex_unlock(&philo->data->mutex_print);
		philo_usleep(philo, philo->data->time_to_sleep);
		return (1);
	}
	return (0);
}

void	think_and_die(t_philo *philo)
{
	int	time_to_think;

	time_to_think = 0;
	time_to_think = philo->data->time_to_die
		- philo->data->time_to_eat - philo->data->time_to_sleep;
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%lld %d is thinking\n", t_diff(philo->data->t_time),
		philo->i + 1);
	pthread_mutex_unlock(&philo->data->mutex_print);
	philo_usleep(philo, time_to_think);
}

int	thinking(t_philo *philo)
{
	if (check_death(philo) == 0 && mutex_check_death(philo) == 0)
	{
		if (((philo->data->number_of_philo % 2 == 0)
				&& philo->data->time_to_eat > philo->data->time_to_sleep
				&& (philo->data->time_to_eat > philo->data->time_to_die / 2))
			|| ((philo->data->number_of_philo % 2 != 0)
				&& philo->data->time_to_eat >= philo->data->time_to_sleep
				&& (philo->data->time_to_eat + philo->data->time_to_sleep
					> philo->data->time_to_die / 2)))
			think_and_die(philo);
		else
		{	
			pthread_mutex_lock(&philo->data->mutex_print);
			printf("%lld %d is thinking\n", t_diff(philo->data->t_time),
				philo->i + 1);
			pthread_mutex_unlock(&philo->data->mutex_print);
			usleep(100);
		}
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	if (check_death(philo) == 0 && mutex_check_death(philo) == 0)
	{
		if (philo->data->number_of_philo == 1)
			return (one_philo(philo), 0);
		if (philo->i % 2 == 0)
		{
			if (eating_even(philo) == 0)
				return (0);
		}
		else
		{
			if (eating_uneven(philo) == 0)
				return (0);
		}
		return (1);
	}
	return (0);
}
