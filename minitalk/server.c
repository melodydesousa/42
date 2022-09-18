/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:03:29 by mede-sou          #+#    #+#             */
/*   Updated: 2022/09/15 17:38:36 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_make_str(char *str, char c)
{
	int		i;
	int		size;
	char	*new_str;

	i = 0;
	size = ft_strlen(str);
	new_str = malloc(sizeof(char) * (size + 2));
	if (new_str == NULL)
		return (NULL);
	while (i < size)
	{
		new_str[i] = str[i];
		i++;
	}
	if (new_str == NULL || !c)
		return (NULL);
	new_str[i] = c;
	new_str[i + 1] = '\0';
	return (new_str);
}

char	binary_to_char(char *str)
{
	int		i;
	int		j;
	int		res;

	i = 0;
	j = 7;
	res = 0;
	while (i < 8)
	{
		res = res + ((str[i] - 48) * ft_iterative_power(2, j));
		i++;
		j--;
	}
	return ((char)res);
}

void	signal_handler(int signum)
{
	char		c;
	static char	*str;
	static char	*stock_str;

	// if (str)
	// 	ft_printf("str = %s\n", str);
	// if (stock_str)
	// 	ft_printf("stock_str = %s\n", stock_str);
	if (signum == SIGUSR1)
		c = '0';
	else if (signum == SIGUSR2)
		c = '1';
	else if (signum == SIGINT)
	{
		if (str)
			free(str);
		if (stock_str)
			free(stock_str);
		exit (0);
	}
	else
	{
		ft_printf("Error: unknown signal\n");
		return ;
	}
	if (!str)
		str = calloc(1, 1);
	str = ft_make_str(str, c);
	if (str == NULL)
		return ;
	if (ft_strlen(str) == 8)
	{
		if (binary_to_char(str) == '\0')
		{
			ft_printf("Received: %s\n", stock_str);
			free(stock_str);
			// stock_str = NULL;
			// ft_printf("stock str: %p\n", stock_str);
			pause();
		}
		if (!stock_str)
			stock_str = calloc(1, 1);
		stock_str = ft_make_str(stock_str, binary_to_char(str));
		free(str);
		if (stock_str == NULL)
			return ;
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
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// sigaction(SIGINT, &sa, NULL);
	while (1)
	{
	}
	return (0);
}
