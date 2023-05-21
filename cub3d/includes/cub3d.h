/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:39:25 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/06 17:01:54 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../sources/libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <errno.h>

typedef struct s_ray
{
	float	dir_x;
	float	dir_y;
	float	plan_x;
	float	plan_y;
	int		map_x;
	int		map_y;
	float	ray_dir_x;
	float	ray_dir_y;
	float	camera_x;
	float	side_dist_x;
	float	side_dist_y;
	float	d_dist_x;
	float	d_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	float	p_wall_dist;
	float	wall_x;
	int		line_h;
	int		draw_start;
	int		draw_end;
}				t_ray;

typedef struct s_map
{
	int		count;
	int		first_line;
	int		last_line;
	int		largest_line;
	char	**map;
}				t_map;

typedef struct s_path
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	void	*no;
	void	*ea;
	void	*so;
	void	*we;
}				t_path;

typedef struct s_color
{
	char	*p;
	int		i;
	int		count;
	int		r;
	int		g;
	int		b;
	char	r_hex[3];
	char	g_hex[3];
	char	b_hex[3];
	char	*color_hex;
	int		color_int;
}				t_color;

typedef struct s_img
{
	void	*mlx_img;
	int		*addr;
	int		bpp;
	int		width;
	int		height;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_tex
{
	int		tex_x;
	int		tex_y;
	int		width;
	int		height;
	float	step;
	float	tex_pos;
	int		color;
	t_img	img;
}				t_tex;

typedef struct s_data
{
	t_path	path;
	t_color	c;
	t_color	f;
	t_img	img;
	t_map	map;
	t_tex	tex[4];
	char	**tab;
	char	**new_tab;
	char	*check_tab[7];
	int		int_tab[6];
	char	*line;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*p;
	void	*b;
	int		c_i;
	int		c_j;
	int		sizex;
	int		sizey;
	int		rx;
	int		ry;
	int		size_line;
	int		size_map;
	int		largest_line;
	int		last_info;
	int		make_i;
	int		make_k;
	int		make_count;
	int		fichier;
	int		i;
	int		error;
	int		j;
	int		tab_x;
	int		tab_y;
	int		x;
	int		y;
	float	p_x;
	float	p_y;
	float	pos_x;
	float	pos_y;
	int		h;
	int		l;
	int		count;
	int		color_floor_hex;
	int		color_ceiling_hex;
	t_ray	ray;
}				t_data;

# define UP_W 119
# define LEFT_A 97
# define DOWN_S 115
# define RIGHT_D 100
# define ROTATE_LEFT 65361
# define ROTATE_RIGHT 65363
# define ESC 65307
# define X 17

//MAKE TAB**
int		ft_read_map(t_data *d, char *str);
int		ft_first_read(t_data *d, char *str);
int		init_tab(char *arv, t_data *d);
void	init_tab_line(int fd, char **tab, t_data *d);
int		size_map(char *arv);
int		correct_map(t_data *data, int first, int last);

//MAKE PATH
int		make_path(char *str, char *compare, t_data *d);
int		make_path_2(char *compare, t_data *d, int c, int j);
int		ft_pass_path(char *str, char *compare);
int		make_path_color(char *str, char *compare, t_data *d, int c);
int		check_all_path(t_data *data);
int		save_path(char *str, t_data *data);
int		save_path_no_so_we(char *str, t_data *data);
int		save_path_ea_c_f(char *str, t_data *data);

//CHECK ERRORS
int		check_argv(char *str);
int		check_if_doublon(char *str, char *check_str);
int		check_doublon_path(t_data *data);
int		check_tab_doublon(t_data *data);
void	init_check_tab(t_data *data);
int		check_if_tab(char *str, char **tab);
int		check_colors(t_color *color, t_data *d);
int		check_zero(t_data *data);
int		check_x_in_top_line(char *str, int j);
int		check_x_in_down_line(char *str, int j);
int		check_x_in_line(char *str, int j);
int		check_backslash_zero(t_data *data);

//COLORS
int		make_colors(t_color *color, t_data *data);
void	free_split_tab(char **tab);

//INIT
int		ft_init_images(t_data *d);
int		ft_init_struct(t_data *d);

//MAP
int		count_largest_line(t_data *data);
int		remake_map(t_data *data);
int		remake_map2(t_data *data);
int		save_last_info(t_data *data);
int		new_map(t_data *data, int j);
int		check_first_line(t_data *data, int j);
int		check_last_line(t_data *data, int j);
int		check_after_last_line(t_data *data);
int		check_map_caracters(char *str, t_map *map);
int		check_borders(t_data *data, int i, int j, int k);
void	set_player_info(t_data *data);

char	**make_new_tab2(t_data *data, int first, int last);
char	**make_new_tab3(char **tab, t_data *data, int first, int last);
char	*make_last_line(char *str, t_data *data);
int		correct_map(t_data *data, int first, int last);

//UTILS
int		ft_strlen_cub3d(char *str);
char	*ft_dup_solong(char *s, int len);
void	ft_memset_cub3d(void *s, int c, size_t n);
int		ft_strcmp(char *s1, char *s2);
void	free_tab(t_data *d);
void	print_tab(t_data *data);
void	print_tab_def(t_data *data);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcpy_path(char *dest, char *src);
char	*ft_strcpy_color(char *dest, char *src);
char	*ft_strcpy_map(char *dest, char *src, int len);

//DESTROY & FREE
int		destroy_mlx(t_data	*d);
void	free_tab(t_data *d);

//INIT MINILIBX
int		init_minilibx(t_data *d);
int		deal_key(int key, t_data *d);
int		ft_close(t_data *d);
int		get_textures1(t_data *d);
int		get_textures2(t_data *d);

//RAY CASTING
int		ray_casting(t_data *d);
int		draw_ceiling_floor(t_data *d, int x, int y);
void	draw(t_data *d, int i);
void	init_vectors(t_data *d);
void	init_vectors_N_S(t_data *d);

#endif