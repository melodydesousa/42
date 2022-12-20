/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:33:14 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/20 13:10:07 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_data  data;
    
    ft_memset_cub3d(&data, 0, sizeof(t_data));
	printf("data.ray.dir_x = %f\n", data.ray.dir_x);
    if (argc != 2)
        return (0);
    if (check_argv(argv[1]) == 0)
        return (0);
    if (ft_read_map(&data, argv[1]) == 0)
        return (0);
    print_tab(data.tab);
    if (check_tab_doublon(&data) == 0)
        return (0);
	else
		init_minilibx(&data);
	ray_casting(&data);
	mlx_hook(data.win_ptr, 02, 1L << 0, deal_key, &data);
	mlx_hook(data.win_ptr, X, 1L << 2, ft_close, &data);
	mlx_loop(data.mlx_ptr);
    return (0);
}