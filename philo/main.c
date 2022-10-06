/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:16:01 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/06 17:06:56 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_arg(t_data *data, char **av)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	if (data->number_of_philosophers == -1)
		return (1);
	data->time_to_die = ft_atoi(av[2]);
	if (data->time_to_die == -1)
		return (1);
	data->time_to_eat = ft_atoi(av[3]);;
	if (data->time_to_eat == -1)
		return (1);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_sleep == -1)
		return (1);
	if (av[5])
	{
		data->x_must_eat = ft_atoi(av[5]);
		if (data->x_must_eat == -1)
			return (1);
	}
	pthread_mutex_init(&data->mutex_forks[250], NULL);
	return (0);
}

void	ft_destroy(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_destroy(&philo[i].mutex_print);
	pthread_mutex_destroy(&data->mutex_forks[250]);
	pthread_mutex_destroy(&philo[i].mutex_death);
	pthread_mutex_destroy(&philo[i].mutex_create);
}

void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo[i].data = data;
	philo[i].index = i;
	philo[i].death = 0;
	philo[i].has_ate = 0;
	pthread_mutex_init(&philo[i].mutex_print, NULL);
	pthread_mutex_init(&philo[i].mutex_death, NULL);
	pthread_mutex_init(&philo[i].mutex_create, NULL);
}

int	check_death(t_philo *philo)
{
	if (philo->last_time_ate > (timestamp() - philo->data->time_to_die))
	{
		pthread_mutex_lock(&philo->mutex_print);
		philo->death = 1;
		printf("%lld %d is dead\n", (timestamp() - philo->data->first_time), philo->index);
		pthread_mutex_unlock(&philo->mutex_print);
		return (-1);
	}
	else if (philo->data->x_must_eat && (philo->has_ate == philo->data->x_must_eat))
		return (-1);
	return (0);
}

void *routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mutex_create);
	while (philo->death == 0)
	{
		if (check_death(philo) == -1)
			return (NULL);
		pthread_mutex_lock(&philo->data->mutex_forks[philo->index]);
		pthread_mutex_lock(&philo->data->mutex_forks[philo->index + 1]);
		pthread_mutex_lock(&philo->mutex_print);
		printf("%lld %d is eating\n", (timestamp() - philo->data->first_time), philo->index);
		philo->last_time_ate = timestamp() - philo->data->first_time;
		philo->has_ate++;
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->mutex_print);
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->index]);
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->index + 1]);
		// if (check_death(philo) == -1)
		// 	return (NULL);
		pthread_mutex_lock(&philo->mutex_print);
		printf("%lld %d is sleeping\n", (timestamp() - philo->data->first_time), philo->index);
		pthread_mutex_unlock(&philo->mutex_print);
		usleep(philo->data->time_to_sleep * 1000);
		pthread_mutex_lock(&philo->mutex_print);
		printf("%lld %d is thinking\n", (timestamp() - philo->data->first_time), philo->index);
		pthread_mutex_unlock(&philo->mutex_print);
	}
	pthread_mutex_unlock(&philo->mutex_create);
	return (NULL);
}

int main(int ac, char **av) 
{
	t_data			data;
	int				i;
	t_philo 		*philo;

	if (ac == 5 || ac == 6)
	{
		if (init_arg(&data, av) == 1)
			return (0);
		philo = malloc(sizeof(t_philo) * data.number_of_philosophers);
		i = 0;
		data.first_time = timestamp();
		while (i < data.number_of_philosophers)
		{
			init_philo(philo, &data, i);
			pthread_mutex_lock(&philo[i].mutex_create);
			if (pthread_create(&philo[i].threads, NULL, routine, &philo[i]) != 0)
			{
				ft_destroy(philo, &data, i);
				return (0);
			}
			pthread_mutex_unlock(&philo[i].mutex_create);
			i++;
		}
		i = 0;
		while (philo[i].death == 0 && i < data.number_of_philosophers)
		{
			pthread_join(philo[i].threads, NULL);
			i++;
		}
	}
	ft_destroy(philo, &data, i);
	return (0);
}