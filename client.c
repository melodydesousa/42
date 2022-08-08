/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:03:39 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 17:16:43 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

static void	conversion(int server_id, char c)
{
	int	i;
	i = 7;
	if ()
		kill(server_id, SIGUSR1);
	else
		kill(server_id, SIGUSR2);
	usleep(100);
	i++;
}

int	main(int ac, char **av)
{
	pid_t	server_id;
	int		i;

	i = 0;
	if (ac != 3)
		return (-1);
	server_id = ft_atoi(av[1]);
	while (av[2][i])
	{
		conversion(server_id, av[2][i]);
		i++;
	}
	return (0);
}