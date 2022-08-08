/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:03:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 17:18:52 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minitalk.h"

void	signal_handler(int signum)
{
	ft_printf("Message received from signal nb%d\n", signum);
}

int	main()
{
	struct sigaction sa;
	pid_t	id;

	id = getpid();
	ft_printf("Server id = %d\n", id);
	sa.sa_handler = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sleep(5);
	while (1)
	{
		
	}
	return (0);
}