/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:03:39 by mede-sou          #+#    #+#             */
/*   Updated: 2022/09/29 11:59:46 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_binary(int server_id, char c)
{
	int	i;
	int	tab[BUFFER];

	i = 6;
	while (i >= 0)
	{
		tab[i] = c % 2;
		c = c / 2;
		i--;
	}
	i = 0;
	while (i < 7)
	{
		if (tab[i] == 0)
			kill(server_id, SIGUSR1);
		else
			kill(server_id, SIGUSR2);
		i++;
		usleep(200);
	}
}

int	main(int ac, char **av)
{
	pid_t	server_id;
	int		i;

	i = 0;
	server_id = ft_atoi(av[1]);
	if (server_id <= 0 || ac != 3 || kill(server_id, 0) != 0)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (server_id > 0)
	{
		while (av[2][i])
		{
			send_binary(server_id, av[2][i]);
			i++;
		}
	}
	send_binary(server_id, '\0');
	exit (0);
	return (0);
}
