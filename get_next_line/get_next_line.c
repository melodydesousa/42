/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:11:52 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/17 19:10:54 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*get_next_line(int fd)
// {
// }


#include "get_next_line.h"

int main()
{
   int	nb_octets;
   int	fd;
   char *dest;
   
   nb_octets = 1;
   fd = open("test.txt", O_RDONLY);
   if (fd == -1)
   		return (0);
	dest = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!dest)
		return (0);
	while (nb_octets != 0) 
	{
		nb_octets = read(fd, dest, BUFFER_SIZE);
		dest[nb_octets] = '\0';
		ft_putstr(dest);
		ft_putnbr(nb_octets);
	}
    return 0;
}