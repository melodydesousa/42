/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:14:28 by mede-sou          #+#    #+#             */
/*   Updated: 2022/10/06 16:09:29 by mede-sou         ###   ########.fr       */
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

/* memset, printf, malloc, free, write,
usleep, gettimeofday, 
pthread_create, pthread_detach, pthread_join, 
pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
*/

typedef struct s_data {
	int 			number_of_philosophers;
	int 			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long int	first_time;
	int				x_must_eat;
	pthread_mutex_t mutex_forks[250];
} t_data;

typedef struct s_philo {
	t_data			*data;
	int				index;
	pthread_t		threads;
	int				death;
	int				has_ate;
	int				last_time_ate;
	pthread_mutex_t mutex_print;
	pthread_mutex_t mutex_death;
	pthread_mutex_t mutex_create;
	// pthread_mutex_t mutex_fork_right;
} t_philo;

int			ft_atoi(const char *nptr);
long long	timestamp(void);
long long	time_diff(t_data data);
int			pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
/* renvoie	0 → lorsque tout s'est bien passé;
EAGAIN → lorsque les ressources sont insuffisantes ou le nombre de threads maximum est atteint;
EINVAL → lorsqu'un argument invalide est passé en paramètre;
EPERM → lorsqu'il y a un problème de droit sur l'ordonnanceur (passé en paramètre); */

int pthread_join(pthread_t thread, void **retval);
/* Pour attendre la fin de l'exécution du thread
*thread est une référence vers la variable qui va contenir le thread;
**retval est un pointeur vers un entier qui contiendra la valeur de retour du thread;
0 → lorsque tout s'est bien passé;
EDEADLK → lorsqu'il y a un deadlock;
EINVAL → lorsque le thread n'est pas joignable;
ESRCH → si le thread n'existe pas;
*/

int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr );
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

#endif