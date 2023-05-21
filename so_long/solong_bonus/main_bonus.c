/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:06:54 by mede-sou          #+#    #+#             */
/*   Updated: 2022/09/20 15:56:30 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	init_ptr(t_data *d)
{
	d->mlx = NULL;
	d->win = NULL;
	d->chicken = NULL;
	d->chicken_r = NULL;
	d->coop = NULL;
	d->corn = NULL;
	d->wall = NULL;
	d->grass = NULL;
}

int	first_check(char **arv, t_data *d)
{
	if (ft_strnstr(arv[1], ".ber", ft_strlen(arv[1])) == 0)
		return (ft_printf("Error\nInvalid file extension\n"), 1);
	if (init_tab(arv[1], d) == 1 || ft_strlen(arv[1]) < 4)
		return (ft_printf("Error\nInvalid map\n"), 1);
	return (0);
}

int	main(int argc, char **arv)
{
	t_data	d;

	if (argc != 2)
		return (0);
	init_ptr(&d);
	if (first_check(arv, &d) == 1)
		return (1);
	if (check_errors(&d) == 1)
		return (0);
	d.mlx = mlx_init();
	if (d.mlx)
	{
		d.win = mlx_new_window(d.mlx, d.tab_x * N, d.tab_y * N, "so_long");
		if (d.win)
		{
			init_values(&d);
			init_images(&d);
			map_parsing(&d);
			mlx_hook(d.win, 02, 1L << 0, deal_key, &d);
			mlx_hook(d.win, X, 1L << 2, ft_close, &d);
			mlx_loop(d.mlx);
		}
	}
	ft_close(&d);
	return (0);
}
