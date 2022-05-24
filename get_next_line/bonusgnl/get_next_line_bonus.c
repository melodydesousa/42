/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:31:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/24 10:57:14 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_malloc(int len)
{
	char	*s;

	s = malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	s[0] = '\0';
	return (s);
}

int	check_sep(char **save, int octets_lus, int fd)
{
	int	i;

	i = 0;
	while (save[fd])
	{
		if (save[fd][i] == '\n')
			return (1);
		i++;
		octets_lus--;
	}
	return (0);
}

char	*ft_line(char *save, int len)
{
	int			i;
	char		*line;

	i = 0;
	line = ft_malloc(len);
	while (save[i] != '\0' && len >= 0)
	{
		line[i] = save[i];
		if (save[i] == '\n')
		{
			line[i] = save[i];
			i++;
			break ;
		}
		i++;
		len--;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_save(char **save, int nb_octets)
{
	int		i;
	int		j;
	char	*temp_save;
	char	*new_save;

	i = -1;
	temp_save = *save;
	while (temp_save[++i] != '\0' && nb_octets > 0)
	{
		if (temp_save[i] == '\n')
			break ;
		nb_octets--;
	}
	new_save = ft_malloc(nb_octets);
	j = 0;
	i++;
	while (--nb_octets + 1 > 0)
	{
		new_save[j] = temp_save[i + j];
		j++;
	}
	new_save[j] = '\0';
	free(temp_save);
	*save = new_save;
	return (new_save);
}

char	*get_next_line(int fd)
{
	// char		dest[BUFFER_SIZE + 1];
	static char	*save[256];
	char		*line;
	int			octets_lus;
	int			i;

	i = 0;
	octets_lus = 1;
	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, save, 0) < 0)
	 	return (0);
	if (!save[fd])
		save[fd] = ft_malloc(1);
	while (check_sep(&save[fd], octets_lus, fd) == 0 && octets_lus > 0)
	{
		// printf("*fd : [%d]\n", fd);
		octets_lus = read(fd, save, BUFFER_SIZE);
		// // printf("*dest : [%s]\n", dest);
		// save[fd] = ft_temp_join(save[fd], dest);
		// printf("*save join : [%s]\n", save[fd]);
		i++;
	}
	if (check_sep(&save[fd], octets_lus, fd) == 1)
	{
		save[fd] = malloc(sizeof(char) * (i + 1));
		save[fd][octets_lus] = '\0';
		save[fd] = ft_save(&save[fd], ft_strlen(save[fd]));
		line = ft_line(save[fd], ft_strlen(save[fd]));
	}
	if (save[fd][0] == '\0')
	{
	 	free(save[fd]);
	 	save[fd] = NULL;
	 	return (NULL);
	}
	// printf("*save fin : [%s]\n", save[fd]);
	return (line);
}


int main()
{
   int	fd1;
   int 	fd2;
   char *line;
  	
	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	if (fd2 == -1 )
   		return (0);
	line = get_next_line(fd1);
	printf("**********line1 fd1 : [%s]\n", line);
	printf("*fd1 : [%d]\n", fd1);
	free(line);
	line = get_next_line(fd2);
	printf("**********line1 fd2 : [%s]\n", line);
	printf("*fd2 : [%d]\n", fd2);
	free(line);
	line = get_next_line(fd1);
	printf("**********line2 fd1 : [%s]\n", line);
	free(line);
	line = get_next_line(fd2);
	printf("**********line2 fd2 : [%s]\n", line);
	free(line);
	// line = get_next_line(fd1);
	// printf("**********line3 fd1 : %s\n", line);
	// free(line);
	// line = get_next_line(fd2);
	// printf("**********line3 fd2 : %s\n", line);
	// free(line);
	// line = get_next_line(fd1);
	// printf("**********line4 fd1 : %s\n", line);
	// free(line);
	// line = get_next_line(fd2);
	// printf("**********line4 fd2 : %s\n", line);
	// free(line);
   return (0);
}
