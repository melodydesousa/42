/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:42:00 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/25 11:42:04 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_check_death(t_philo *philo)
{
	int		check;

	check = 0;
	pthread_mutex_lock(&philo->data->mutex_death);
	check = philo->data->death;
	pthread_mutex_unlock(&philo->data->mutex_death);
	return (check);
}

void	philo_usleep(t_philo *philo, int time_to)
{
	long long int	wake_up;

	wake_up = t_diff(philo->data->t_time) + time_to;
	while (t_diff(philo->data->t_time) <= wake_up)
	{
		if (check_death(philo) == 1 || mutex_check_death(philo) == 1)
			break ;
		usleep(50);
	}
}

int	check_death(t_philo *p)
{
	if (mutex_check_death(p) == 0)
	{
		if (t_diff(p->data->t_time) - p->last_meal > p->data->time_to_die)
		{
			pthread_mutex_lock(&p->data->mutex_death);
			p->data->death = 1;
			pthread_mutex_unlock(&p->data->mutex_death);
			pthread_mutex_lock(&p->data->mutex_print);
			printf("%lld %d died\n", t_diff(p->data->t_time), p->i + 1);
			pthread_mutex_unlock(&p->data->mutex_print);
			return (1);
		}
		if (p->data->x_must_eat != 0 && p->ate == p->data->x_must_eat
			&& p->data->check_x_must_eat >= 0)
		{
			if (p->data->check_x_must_eat == 0)
				return (2);
			pthread_mutex_lock(&p->data->mutex_death);
			p->data->check_x_must_eat--;
			pthread_mutex_unlock(&p->data->mutex_death);
		}
	}
	return (0);
}

void	one_philo(t_philo *philo)
{
	printf("%lld %d has taken a fork\n", t_diff(philo->data->t_time),
		philo->i + 1);
	usleep((philo->data->time_to_die - t_diff(philo->data->t_time)) * 1000);
	printf("%lld %d died\n", t_diff(philo->data->t_time), philo->i + 1);
}
