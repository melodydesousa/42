/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:33:14 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/06 14:47:09 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	d;

	ft_memset_cub3d(&d, 0, sizeof(t_data));
	if (argc != 2)
		return (ft_putstr_fd("Error\nWrong arguments\n", 2), 1);
	if (check_argv(argv[1]) == -1)
		return (1);
	if (init_tab(argv[1], &d) == -1)
		return (1);
	if (check_tab_doublon(&d) == -1)
		return (1);
	if (check_colors(&d.c, &d) == -1 || check_colors(&d.f, &d) == -1)
		return (1);
	if (make_colors(&d.c, &d) == -1 || make_colors(&d.f, &d) == -1)
		return (1);
	if (remake_map(&d) == -1)
		return (1);
	if (init_minilibx(&d) == -1)
		return (ft_putstr_fd("Error\nMlx failed\n", 2), 1);
	mlx_hook(d.win_ptr, 02, 1L << 0, deal_key, &d);
	mlx_hook(d.win_ptr, X, 1L << 2, ft_close, &d);
	mlx_loop(d.mlx_ptr);
	free_tab(&d);
	return (0);
}
