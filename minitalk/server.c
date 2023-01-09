/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:03:29 by mede-sou          #+#    #+#             */
/*   Updated: 2023/01/09 11:40:59 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum)
{
	static char	str[BUFFER];
	static char	*stock_str;
	char		*tmp;

	make_c(signum, str, stock_str);
	if (ft_strlen(str) == 7)
	{
		if (binary_to_char(str) == '\0')
		{
			ft_printf("Received: %s\n", stock_str);
			free(stock_str);
			stock_str = NULL;
		}
		tmp = stock_str;
		stock_str = ft_make_stock(stock_str, binary_to_char(str));
		free(tmp);
		if (stock_str == NULL)
			return ;
		str[0] = '\0';
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	pid_t				id;

	(void)ac;
	(void)**av;
	id = getpid();
	ft_printf("Server id: %d\n", id);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
	}
	return (0);
}
