/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:11:52 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/18 17:52:30 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_save(char *dest, int nb_octets)
{
	int			i;
	int			j;
	static char	*save;
    
    i = 0;
	while (dest[i] != '\0' && nb_octets > 0)
    {
       	if (dest[i] == '\n')
            break ;
        i++;
        nb_octets--;
    }
    j = 0;
    while (dest[i + j] != '\0' || nb_octets > 0)
    {
        save[j] = dest[i + j];
        j++;
        nb_octets--;
    }
    save[j + 1] = '\0';
	printf("save : %s\n", save);
    return(save);
    
}

char *ft_line(char *dest, int nb_octets)
{
	int			i;
	int			j;
	char		*line;
    
    i = 0;
	line = malloc(sizeof(char) * (nb_octets + 2));
    while (dest[i] != '\0' && nb_octets > 0)
    {
        line[i] = dest[i];
        if (dest[i] == '\n')
            break ;
        i++;
        nb_octets--;
    }
    line[i + 1] = '\0';
	printf("line ds ft: %s\n", line);
    return(line);
    
}

char    *get_next_line(int fd)
{
    char		dest[BUFFER_SIZE];
    char		*line;
    static char	*save;
	int			nb_octets;

	if(fd == -1 || BUFFER_SIZE <= 0 || read(fd, dest, 0) < 0)
        return(0);
	nb_octets = read(fd, dest, BUFFER_SIZE);
	if (save)
	{
		line = ft_line(save, nb_octets);
		printf("line si save inexitant : %s\n", line);
	}
	else		
  		line = ft_line(dest, nb_octets);
	save = get_save(dest, nb_octets);
	printf("save cree : %s\n", save);
	printf("line apres avoir cree save: %s\n", line);
	return(line);
}


#include "get_next_line.h"

int main()
{
   int	fd;
   char	*line;
   
  	
	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	if (fd == -1)
   		return (0);
	printf("%s\n", line);
	close(fd);
   return (0);
}