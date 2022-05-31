/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:31:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/31 10:15:10 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_malloc(int len)
{
	char	*s;

	s = malloc(sizeof(char) * (len + 1));
	if (s == NULL)
		return (NULL);
	s[0] = '\0';
	return (s);
}

int	check_sep(char *save, int octets_lus)
{
	int	i;

	i = 0;
	while (save[i])
	{
		if (save[i] == '\n')
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
	static char	dest[BUFFER_SIZE + 1];
	static char	*save;
	char		*line;
	int			octets_lus;

	octets_lus = 1;
	if (fd == -1 || BUFFER_SIZE <= 0 || read(fd, dest, 0) < 0)
		return (0);
	if (!save)
		save = ft_malloc(1);
	while (check_sep(save, octets_lus) == 0 && octets_lus > 0)
	{
		octets_lus = read(fd, dest, BUFFER_SIZE);
		dest[octets_lus] = '\0';
		save = ft_temp_join(save, dest);
	}
	if (save[0] == '\0')
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	line = ft_line(save, ft_strlen(save));
	save = ft_save(&save, ft_strlen(save));
	return (line);
}

/*
int main()
{
   int	fd;
   char *line;
  	
	fd = open("test2.txt", O_RDONLY);
	if (fd == -1)
   		return (0);
	line = get_next_line(fd);
	printf("**********line1 : [%s]\n", line);
	free(line);
	line = get_next_line(fd);
	printf("**********line2 : [%s]\n", line);
	free(line);
	line = get_next_line(fd);
	printf("**********line3 : [%s]\n", line);
	free(line);
	line = get_next_line(fd);
	printf("**********line4 : [%s]\n", line);
	free(line);
	line = get_next_line(fd);
	printf("**********line5 : %s\n", line);
	free(line);
	line = get_next_line(fd);
	printf("**********line6 : %s\n", line);
	free(line);
	// line = get_next_line(fd);
	// printf("**********line7 : %s\n", line);
	// free(line);
	// line = get_next_line(fd);
	// printf("**********line8 : %s\n", line);
	// free(line);
   return (0);
}
*/