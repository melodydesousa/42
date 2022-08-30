/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:54:57 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/30 15:03:32 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "libft/printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*chicken;
	void	*grass;
	void	*wall;
	void	*corn;
	void	*coop;
	void	*anim;
	int		x;
	int		y;
	int		x_p;
	int		y_p;
	int		wid;
	int		hei;
	char	**tab;
	int		tab_x;
	int		tab_y;
	int		size_map;
	int		size_line;
	int		collect;
	int		player;
	int		no_valid_carac;
	int		count;
	int		exit;
	char	*count_str;
}				t_data;

# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define X 17
# define MIN 25
# define N 64

// Initialization
void	init_values(t_data	*d);
void	init_images(t_data	*d);
void	map_parsing(t_data *d);
int		size_map(char *arv);
int		init_tab(char *arv, t_data *d);

// Check errors
void	check_tab_content(t_data *d);
int		check_format_map(t_data *d);
int		check_errors(t_data *d);
void	set_player_position(t_data *d);

// Handle events
int		deal_key(int key, t_data *d);
void	handle_event_w(t_data *d);
void	handle_event_s(t_data *d);
void	handle_event_d(t_data *d);
void	handle_event_a(t_data *d);
int		ft_count_event(int key, t_data *d);

// Close program
int		ft_close(t_data *d);

#endif