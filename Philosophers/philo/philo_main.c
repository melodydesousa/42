/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:16:01 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/25 12:19:25 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy(t_philo *philo)
{
	int	j;

	j = 0;
	while (j < philo->data->number_of_philo)
	{
		pthread_mutex_destroy(&philo->data->mutex_forks[j]);
		j++;
	}
	pthread_mutex_destroy(&philo->data->mutex_print);
	pthread_mutex_destroy(&philo->data->mutex_death);
	free(philo->data->mutex_forks);
	free(philo);
}

void	*routine(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	while (check_death(phi) == 0 && mutex_check_death(phi) == 0)
	{
		if (eating(phi) == 0)
			break ;
		if (sleeping(phi) == 0)
			break ;
		if (thinking(phi) == 0)
			break ;
		if (check_death(phi) == 1 || mutex_check_death(phi) == 1)
			break ;
	}
	return (NULL);
}

int	ft_create(t_philo *p, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		init_philo(p, data, i);
		if (pthread_create(&p[i].threads, NULL, routine, &p[i]) != 0)
			return (ft_destroy(p), 0);
		usleep(20);
		i = i + 2;
	}
	i = 1;
	while (i < data->number_of_philo)
	{
		init_philo(p, data, i);
		if (pthread_create(&p[i].threads, NULL, routine, &p[i]) != 0)
			return (ft_destroy(p), 0);
		usleep(20);
		i = i + 2;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;
	t_philo	*p;

	p = NULL;
	if (ac < 5)
		printf("Error\nNot enough arguments\n");
	if (ac == 5 || ac == 6)
	{
		if (init_arg(&data, av) == 1)
			return (0);
		p = malloc(sizeof(t_philo) * data.number_of_philo);
		if (p == NULL)
			return (0);
		i = 0;
		data.t_time = timestamp();
		if (ft_create(p, &data) == 0)
			return (0);
		i = -1;
		while (++i < data.number_of_philo)
			pthread_join(p[i].threads, NULL);
	}
	if (p)
		ft_destroy(p);
	return (0);
}
