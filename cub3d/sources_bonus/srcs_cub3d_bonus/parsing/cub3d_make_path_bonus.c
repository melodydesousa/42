/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_make_path_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:44:57 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/06 13:43:25 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	make_path_2(char *compare, t_data *d, int c, int j)
{
	while (d->tab[d->make_i][j] == ' ' && d->tab[d->make_i][j] != '\0')
		j++;
	while (d->tab[d->make_i][j] == compare[c] && compare[c] != '\0')
	{
		c++;
		j++;
	}
	while (d->tab[d->make_i][j] == ' ' && d->tab[d->make_i][j] != '\0')
		j++;
	d->make_k = j;
	while (d->tab[d->make_i][j] != ' ' && d->tab[d->make_i][j] != '\0')
		j++;
	d->make_count = j - d->make_k;
	while (d->tab[d->make_i][j] == ' ' && d->tab[d->make_i][j] != '\0')
		j++;
	if (d->tab[d->make_i][j] != ' ' && d->tab[d->make_i][j] != '\0')
		return (-1);
	return (0);
}

int	make_path(char *str, char *compare, t_data *d)
{
	int	j;
	int	c;

	d->make_count = 0;
	d->make_i = 0;
	j = 0;
	c = 0;
	while (d->tab[d->make_i])
	{
		if (ft_strnstr(d->tab[d->make_i], str, 2) == 0)
		{
			if (make_path_2(compare, d, c, j) == -1)
				return (ft_putstr_fd("Error\nToo many paths\n", 2), -1);
			return (0);
		}
		d->make_i++;
	}
	return (0);
}

int	make_path_color(char *str, char *compare, t_data *d, int c)
{
	d->c_i = 0;
	d->c_j = 0;
	while (d->tab[d->c_i])
	{
		if (ft_strnstr(d->tab[d->c_i], str, (int)ft_strlen(str)) == 0)
		{
			while (d->tab[d->c_i][d->c_j] == ' '
				&& d->tab[d->c_i][d->c_j] != '\0')
					d->c_j++;
			while (d->tab[d->c_i][d->c_j] == compare[c] && compare[c] != '\0')
			{
				c++;
				d->c_j++;
			}
			while (d->tab[d->c_i][d->c_j] == ' '
				&& d->tab[d->c_i][d->c_j] != '\0')
					d->c_j++;
			d->make_k = d->c_j;
			while (d->tab[d->c_i][d->c_j] != '\0')
				d->c_j++;
			return (d->make_count = d->c_j - d->make_k, d->make_i = d->c_i, 0);
		}
		d->c_i++;
	}
	return (0);
}
