/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:16:02 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/25 12:08:59 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_eat(t_philo *p, char *str)
{
	if (check_death(p) != 1 && mutex_check_death(p) == 0)
	{
		pthread_mutex_lock(&p->data->mutex_print);
		printf("%lld %d %s\n", t_diff(p->data->t_time), p->i + 1, str);
		pthread_mutex_unlock(&p->data->mutex_print);
		return (1);
	}
	return (0);
}

void	unlock_even(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->i]);
	if (philo->i == philo->data->number_of_philo - 1)
		pthread_mutex_unlock(&philo->data->mutex_forks[0]);
	else
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->i + 1]);
}

int	eating_even(t_philo *p)
{
	if (check_death(p) != 1 && mutex_check_death(p) == 0)
	{
		pthread_mutex_lock(&p->data->mutex_forks[p->i]);
		if (p->i == p->data->number_of_philo - 1)
			pthread_mutex_lock(&p->data->mutex_forks[0]);
		else
			pthread_mutex_lock(&p->data->mutex_forks[p->i + 1]);
		if (print_eat(p, "has taken a fork") == 1)
		{
			print_eat(p, "has taken a fork");
			print_eat(p, "is eating");
			p->last_meal = t_diff(p->data->t_time);
			p->ate++;
			if (check_death(p) != 1 && mutex_check_death(p) == 0)
				philo_usleep(p, p->data->time_to_eat);
			return (unlock_even(p), 1);
		}
		unlock_even(p);
	}
	return (0);
}

void	unlock_uneven(t_philo *philo)
{
	if (philo->i == philo->data->number_of_philo - 1)
		pthread_mutex_unlock(&philo->data->mutex_forks[0]);
	else
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->i + 1]);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->i]);
}

int	eating_uneven(t_philo *p)
{
	if (check_death(p) != 1 && mutex_check_death(p) == 0)
	{
		if (p->i == p->data->number_of_philo - 1)
			pthread_mutex_lock(&p->data->mutex_forks[0]);
		else
			pthread_mutex_lock(&p->data->mutex_forks[p->i + 1]);
		pthread_mutex_lock(&p->data->mutex_forks[p->i]);
		if (print_eat(p, "has taken a fork") == 1)
		{
			print_eat(p, "has taken a fork");
			print_eat(p, "is eating");
			p->last_meal = t_diff(p->data->t_time);
			if (check_death(p) != 1 && mutex_check_death(p) == 0)
				philo_usleep(p, p->data->time_to_eat);
			p->ate++;
			return (unlock_uneven(p), 1);
		}
		unlock_uneven(p);
	}
	return (0);
}
