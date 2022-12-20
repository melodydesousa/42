/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:59:03 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/20 17:52:51 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vectors_N_S(t_data *d)
{
	if (d->tab[d->p_y][d->p_x] == 'N')
	{
		d->ray.dir_x = -1.0;
		d->ray.dir_y = 0.0;
		d->ray.plan_y = 0.66; // plan camera (ligne du joueur)
		d->ray.plan_x = 0.0;
	}
	else if (d->tab[d->p_y][d->p_x] == 'S')
	{
		d->ray.dir_x = 1.0;
		d->ray.dir_y = 0.0;
		d->ray.plan_y = -0.66;
		d->ray.plan_x = 0.0;
	}
}

void init_vectors(t_data *d)
{	
	d->p_x = 4;
	d->p_y = 15;
	init_vectors_N_S(d);
	if (d->tab[d->p_y][d->p_x] == 'E')
	{
		d->ray.dir_x = 0.0;
		d->ray.dir_y = 1.0;
		d->ray.plan_x = 0.66;
		d->ray.plan_y = 0.0;
	}
	else if (d->tab[d->p_y][d->p_x] == 'W')
	{
		d->ray.dir_x = 0.0;
		d->ray.dir_y = -1.0;
		d->ray.plan_x = -0.66;
		d->ray.plan_y = 0.0;
	}
	printf("dir_x = %f\n", d->ray.dir_x);
	printf("dir_y = %f\n", d->ray.dir_y);
	printf("plan_x = %f\n", d->ray.plan_x);
	printf("plan_y = %f\n", d->ray.plan_y);
}

void	ray_pos_and_direction(t_data *d, int i)
{
	// Calcul de la direction et position du rayon
	d->ray.camera_x = 2 * i / (double)d->size_map - 1; // gauche = -1, milieu = 0, droite = 1
	d->ray.ray_dir_x = d->ray.dir_x + d->ray.plan_x * d->ray.camera_x;
	d->ray.ray_dir_y = d->ray.dir_y + d->ray.plan_y * d->ray.camera_x;

	// Pos dans le carre actuel
	d->ray.map_x = (int)d->p_x;
	d->ray.map_y = (int)d->p_y;

	// Calcul de la longueur de x jusqu au prochain x
	d->ray.delta_dist_x = fabs(1 / d->ray.ray_dir_x);
	// Calcul de la longueur de y jusqu au prochain y
	d->ray.delta_dist_y = fabs(1 / d->ray.ray_dir_y);
	d->ray.hit = 0;
	printf("\ncamera_x = %f\n", d->ray.camera_x);
	printf("ray_dir_x = %f\n", d->ray.ray_dir_x);
	printf("ray_dir_y = %f\n", d->ray.ray_dir_y);
	printf("delta_dist_x = %f\n", d->ray.delta_dist_x);
	printf("delta_dist_y = %f\n", d->ray.delta_dist_y);
}

void	calculate_move_and_distance(t_data *d)
{
	// Calcul du move et de la longueur du rayon jusqu a la prochaine intersection - distance perpendiculaire
	if (d->ray.ray_dir_x < 0)
	{
		d->ray.step_x = -1;
		printf("\n**map_x = %d\n", d->ray.map_x);
		printf("**map_y = %d\n", d->ray.map_y);
		printf("**p_x = %d\n", d->p_x);
		printf("**p_y = %d\n", d->p_y);
		d->ray.side_dist_x = (d->p_x - d->ray.map_x) * d->ray.delta_dist_x;
	}
	else
	{
		d->ray.step_x = 1;
		d->ray.side_dist_x = (d->ray.map_x + 1.0 - d->p_x) * d->ray.delta_dist_x;
	}
	if (d->ray.ray_dir_y < 0)
	{
		d->ray.step_y = -1;
		d->ray.side_dist_y = (d->p_y - d->ray.map_y) * d->ray.delta_dist_y;
	}
	else
	{
		d->ray.step_y = 1;
		d->ray.side_dist_y = (d->ray.map_y + 1.0 - d->p_y) * d->ray.delta_dist_y;
	}
}

void	calculate_draw_start_and_end(t_data *d)
{
	while (d->ray.hit == 0) // Tant qu'on a pas touché un mur on continue pour savoir ou s arreter
	{
		// On regarde si on est plus proche d'un mur en x ou en y
		if (d->ray.side_dist_x < d->ray.side_dist_y)
		{
			d->ray.side_dist_x = d->ray.side_dist_x + d->ray.delta_dist_x;
			d->ray.map_x = d->ray.map_x + d->ray.step_x;
			d->ray.side = 0; // On a touché un mur en x
		}
		else
		{
			d->ray.side_dist_y = d->ray.side_dist_y + d->ray.delta_dist_y;
			d->ray.map_y = d->ray.map_y + d->ray.step_y;
			d->ray.side = 1; // On a touché un mur en y
		}
		// Si on touche un mur, on sort de la boucle
		printf("d->tab[%d][%d] = %c\n", d->ray.map_y, d->ray.map_x, d->tab[d->ray.map_y][d->ray.map_x]);
		if (d->tab[d->ray.map_y][d->ray.map_x] == '1')
			d->ray.hit = 1;
	}
}

int	ray_casting(t_data *d)
{
	int	i;

	i = 0;
	// printf("\n********RAY CASTING********\n");
	init_vectors(d);
	//INIT SIZE MAP
	d->size_map = 14 * PX;
	while (i < d->size_map)
	{
		ray_pos_and_direction(d, i);
		calculate_move_and_distance(d);
		calculate_draw_start_and_end(d);
		// Calcul de la distance entre le joueur et le mur
		printf("\nside = %d\n", d->ray.side);
		printf("side_dist_x = %f\n", d->ray.side_dist_x);
		printf("side_dist_y = %f\n\n", d->ray.side_dist_y);
		if (d->ray.side == 0)
			d->ray.p_wall_dist = d->ray.side_dist_x - d->ray.delta_dist_x;
		else
			d->ray.p_wall_dist = d->ray.side_dist_y - d->ray.delta_dist_y;
		printf("\np_wall_dist = %f\n", d->ray.p_wall_dist);
		
		// Calcul de la hauteur du mur (ce qu il reste a afficher sur l ecran moins la distance entre le joueur et le mur)
		if (d->ray.p_wall_dist == 0)
			d->ray.p_wall_dist = 0.0001;
		d->ray.line_h = (int)(d->size_map / d->ray.p_wall_dist);
		printf("line_h = %d\n", d->ray.line_h);
		printf("d->size_map = %d\n", d->size_map);

		
		d->ray.draw_start = -d->ray.line_h / 2 + d->size_map / 2;
		if (d->ray.draw_start < 0)
			d->ray.draw_start = 0;
		d->ray.draw_end = d->ray.line_h / 2 + d->size_map / 2;
		if (d->ray.draw_end >= d->size_map)
			d->ray.draw_end = d->size_map - 1;
		printf("draw_start = %d\n", d->ray.draw_start);
		printf("draw_end = %d\n", d->ray.draw_end);
		draw_floor_ceiling(d, i);
		i++;
	}
	return (0);
}
