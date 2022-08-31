/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c		                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:55:01 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/26 11:08:16 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	map_parsing2(t_data *d)
{
	if (d->tab[d->tab_y][d->tab_x] == '1')
		mlx_put_image_to_window(d->mlx, d->win, d->wall, d->x * N, d->y * N);
	else if (d->tab[d->tab_y][d->tab_x] == '0')
		mlx_put_image_to_window(d->mlx, d->win, d->grass, d->x * N, d->y * N);
	else if (d->tab[d->tab_y][d->tab_x] == 'C')
		mlx_put_image_to_window(d->mlx, d->win, d->corn, d->x * N, d->y * N);
	else if (d->tab[d->tab_y][d->tab_x] == 'P')
		mlx_put_image_to_window(d->mlx, d->win,
			d->chicken, d->x_p * N, d->y_p * N);
	else if (d->tab[d->tab_y][d->tab_x] == 'E')
		mlx_put_image_to_window(d->mlx, d->win, d->coop, d->x * N, d->y * N);
	d->tab_x++;
	d->x++;
}

void	map_parsing(t_data *d)
{
	while (d->tab_y < d->size_map && d->tab[d->tab_y])
	{
		d->tab_x = 0;
		d->x = 0;
		while (d->tab[d->tab_y][d->tab_x])
			map_parsing2(d);
		d->tab_y++;
		d->y++;
	}
}

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
	tmp = NULL;
	tmp = get_next_line(fd);
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
		tab[d->tab_y] = ft_dup(line, d->size_line - 1);
		if (tab[d->tab_y] == NULL)
			return ;
		free (line);
		line = get_next_line(fd);
		d->tab_y++;
	}
}

int	init_tab(char *arv, t_data *d)
{
	char	**tab;
	int		fd;

	d->tab_y = 0;
	d->size_map = size_map(arv);
	if (d->size_map == 0 || d->size_map == 1)
		return (1);
	tab = malloc(sizeof(char **) * (d->size_map));
	if (tab == NULL)
		return (1);
	fd = open(arv, O_RDONLY);
	if (fd == -1)
		return (1);
	init_tab_line(fd, tab, d);
	if (tab == NULL)
		return (1);
	d->tab = tab;
	close (fd);
	return (0);
}
