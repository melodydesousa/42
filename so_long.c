/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:55:01 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/17 18:52:42 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct	s_data {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	int		x;
	int		y;
	int		width;
	int		height;
}				t_data;

int	deal_key(int key, t_data *data)
{
	if (key == W)
	{
		// data->img = mlx_xpm_file_to_image(data->mlx_ptr, "./grass.xpm", &data->width, &data->height);
		// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->x, data->y);
		data->y -= 1;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->x * 32, data->y * 32);
	}
	else if (key == S)
	{
		data->y += 1;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->x * 32, data->y * 32);
	}
	else if (key == A)
	{
		data->x -= 1;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->x * 32, data->y * 32);
	}
	else if (key == D)
	{
		data->x += 1;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, data->x * 32, data->y * 32);
	}
	else if (key == ESC)
	{
		exit (0);
	}
	return (0);
}

int	main(int argc, char **arv)
{
	t_data	data;
	int		fd;
	int		i;
	char	*filename;
	char	buffer[1000];

	i = 0;
	argc = 2;
	if (argc == 2)
	{
		data.mlx_ptr = mlx_init();
		data.win_ptr = mlx_new_window(data.mlx_ptr, 500, 500, "test");
		data.x = 0;
		data.y = 0;
		filename = arv[1];
		fd = open(filename, O_RDONLY);
		read(fd, buffer, 1000);
		while (buffer[i])
		{
			if (buffer[i] == 49)
			{
				data.img = mlx_xpm_file_to_image(data.mlx_ptr, "./chicken.xpm", &data.width, &data.height);
				printf("buffer[0] = %d\n", buffer[0]);
				data.x = data.x + 1;
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, data.x * 32, data.y * 32);
			}
			else if (buffer[i] == 48)
			{
				data.img = mlx_xpm_file_to_image(data.mlx_ptr, "./grass.xpm", &data.width, &data.height);
				mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, data.x * 32, data.y * 32);
			}
			i++;
			mlx_key_hook(data.win_ptr, deal_key, &data);
			mlx_loop(data.mlx_ptr);
		}
	}
	// mlx_destroy_image(data.mlx_ptr, data.img);
	// mlx_destroy_window(data.mlx_ptr, data.mlx_ptr);
	return (0);
}