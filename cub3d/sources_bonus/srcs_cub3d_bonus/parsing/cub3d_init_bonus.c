/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:38:08 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/06 15:15:12 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_check_tab(t_data *data)
{
	data->check_tab[0] = "NO\0";
	data->check_tab[1] = "SO\0";
	data->check_tab[2] = "WE\0";
	data->check_tab[3] = "EA\0";
	data->check_tab[4] = "F\0";
	data->check_tab[5] = "C\0";
	data->check_tab[6] = NULL;
}

int	ft_init_images2(t_data *d, int h, int l)
{
	d->path.ea = mlx_xpm_file_to_image(d->mlx_ptr, d->path.path_ea,
			&d->l, &d->h);
	if (!d->path.ea)
		return (write(2, "Error\nProb with img\n", 20), ft_close(d), -1);
	if (d->l != l || d->h != h)
		return (write(2, "Error\nTextures must be the same size\n", 37),
			ft_close(d), -1);
	h = d->h;
	l = d->l;
	d->path.we = mlx_xpm_file_to_image(d->mlx_ptr, d->path.path_we,
			&d->l, &d->h);
	if (!d->path.we)
		return (write(2, "Error\nProb with img\n", 20), ft_close(d), -1);
	if (d->l != l || d->h != h)
		return (write(2, "Error\nTextures must be the same size\n", 37),
			ft_close(d), -1);
	return (0);
}

int	ft_init_images(t_data *d)
{
	int	h;
	int	l;

	d->path.no = mlx_xpm_file_to_image(d->mlx_ptr, d->path.path_no,
			&d->l, &d->h);
	if (!d->path.no)
		return (write(2, "Error\nProb with img\n", 20), ft_close(d), -1);
	h = d->h;
	l = d->l;
	d->path.so = mlx_xpm_file_to_image(d->mlx_ptr, d->path.path_so,
			&d->l, &d->h);
	if (!d->path.so)
		return (write(2, "Error\nProb with img\n", 20), ft_close(d), -1);
	if (d->l != l || d->h != h)
		return (write(2, "Error\nTextures must be the same size\n", 37),
			ft_close(d), -1);
	if (ft_init_images2(d, h, l) == -1)
		return (-1);
	return (0);
}

int	ft_init_struct(t_data *d)
{
	d->mlx_ptr = mlx_init();
	if (!d->mlx_ptr)
	{
		write(2, "Error\nProblem with mlx\n", 23);
		return (-1);
	}
	if (ft_init_images(d) == -1)
		return (-1);
	return (0);
}
