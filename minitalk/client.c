/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:03:39 by mede-sou          #+#    #+#             */
/*   Updated: 2022/09/15 17:04:40 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_binary(int server_id, char *str, char c)
{
	int	i;
	int	*tab;

	tab = malloc(ft_strlen(str) * sizeof(int) * 8);
	if (tab == NULL)
		return ;
	i = 8;
	while (i > 0)
	{
		i--;
		tab[i] = c % 2;
		c = c / 2;
	}
	i = 0;
	while (i < 8)
	{
		if (tab[i] == 0)
			kill(server_id, SIGUSR1);
		else
			kill(server_id, SIGUSR2);
		i++;
		usleep(100);
	}
	free(tab);
}

int	main(int ac, char **av)
{
	pid_t	server_id;
	int		i;

	i = 0;
	if (ac != 3)
		return (-1);
	server_id = ft_atoi(av[1]);
	if (server_id > 0)
	{
		while (av[2][i])
		{
			send_binary(server_id, av[2], av[2][i]);
			i++;
		}
	}
	i = 0;
	while (i < 8)
	{
		send_binary(server_id, av[2], '\0');
		i++;
	}
	exit (0);
	return (0);
}
