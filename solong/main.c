/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:06:54 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/31 11:01:01 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	init_ptr(t_data *d)
{
	d->mlx = NULL;
	d->win = NULL;
	d->chicken = NULL;
	d->coop = NULL;
	d->corn = NULL;
	d->wall = NULL;
	d->grass = NULL;
	d->anim = NULL;
}

int	main(int argc, char **arv)
{
	t_data	d;

	if (argc != 2)
		return (0);
	init_ptr(&d);
	if (ft_strnstr(arv[1], ".ber", ft_strlen(arv[1])) == 0)
		return (ft_printf("Error\nInvalid file extension\n"));
	if (init_tab(arv[1], &d) == 1 || ft_strlen(arv[1]) < 4)
		return (ft_printf("Error\nInvalid map\n"));
	if (check_errors(&d) == 1)
		return (0);
	d.mlx = mlx_init();
	if (d.mlx)
	{
		d.win = mlx_new_window(d.mlx, d.tab_x * N, d.tab_y * N, "so_long");
		init_values(&d);
		init_images(&d);
		map_parsing(&d);
		mlx_hook(d.win, 02, 1L << 0, deal_key, &d);
		mlx_hook(d.win, X, 1L << 2, ft_close, &d);
		mlx_loop(d.mlx);
	}
	ft_close(&d);
	return (0);
}
