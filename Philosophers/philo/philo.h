/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:14:28 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/24 15:56:57 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data {
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long int	t_time;
	int				x_must_eat;
	int				check_x_must_eat;
	int				death;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_death;
	pthread_mutex_t	*mutex_forks;
}	t_data;

typedef struct s_philo {
	t_data			*data;
	int				i;
	int				ate;
	int				last_meal;
	pthread_t		threads;
}	t_philo;

int				ft_atoi(const char *nptr);
long long		timestamp(void);
long long		t_diff(long long int time);
void			philo_usleep(t_philo *philo, int time_to);
void			init_philo(t_philo *philo, t_data *data, int i);
int				init_arg(t_data *data, char **av);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
int				thinking(t_philo *philo);
int				check_death(t_philo *philo);
void			ft_destroy(t_philo *philo);
int				mutex_check_death(t_philo *philo);
void			one_philo(t_philo *philo);
int				eating_even(t_philo *p);
int				eating_uneven(t_philo *p);
void			unlock_uneven(t_philo *philo);
void			unlock_even(t_philo *philo);
int				print_eat(t_philo *p, char *str);

#endif