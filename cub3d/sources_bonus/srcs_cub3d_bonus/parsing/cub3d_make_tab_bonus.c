/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_make_tab_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 12:00:20 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/06 15:13:08 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	size_map(char *arv)
{
	int		i;
	int		fd;
	char	*line;
	char	*tmp;

	i = 0;
	fd = open(arv, O_RDONLY);
	if (fd == -1)
		return (0);
	tmp = get_next_line(fd);
	if (tmp == NULL)
		return (0);
	line = tmp;
	while (line != NULL)
	{
		i++;
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	return (i);
}

void	init_tab_line(int fd, char **tab, t_data *d)
{
	char	*tmp;
	char	*line;

	tmp = get_next_line(fd);
	if (tmp == NULL)
		return ;
	line = tmp;
	while (line != NULL)
	{
		d->size_line = ft_strlen(line);
		tab[d->tab_y] = ft_dup_solong(line, d->size_line - 1);
		if (tab[d->tab_y] == NULL)
			return ;
		free (line);
		line = get_next_line(fd);
		d->tab_y++;
	}
	tab[d->tab_y] = NULL;
}

int	init_tab(char *arv, t_data *d)
{
	char	**tab;
	int		fd;

	d->size_map = size_map(arv);
	if (d->size_map == 0 || d->size_map == 1)
		return (ft_putstr_fd("Error\nInvalid file\n", 2), -1);
	tab = malloc(sizeof(char **) * (d->size_map + 2));
	if (tab == NULL)
		return (-1);
	fd = open(arv, O_RDONLY);
	if (fd == -1)
		return (-1);
	init_tab_line(fd, tab, d);
	if (tab == NULL)
	{
		close (fd);
		return (-1);
	}
	d->tab = tab;
	close (fd);
	return (0);
}

int	save_last_info(t_data *data)
{
	int	j;

	while (data->tab[data->make_i])
	{
		j = 0;
		while (data->tab[data->make_i][j] == ' ')
			j++;
		if (data->tab[data->make_i][j] == '1')
		{
			data->last_info = data->make_i - 1;
			return (1);
		}
		data->make_i++;
	}
	return (0);
}
