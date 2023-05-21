/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_make_colors_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:00:28 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/06 13:43:31 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	make_colors(t_color *color, t_data *data)
{
	char	**tab;

	tab = ft_split(color->p, ',');
	if (tab == NULL)
	{
		free_tab(data);
		return (-1);
	}
	color->r = ft_atoi_color(tab[0]);
	color->g = ft_atoi_color(tab[1]);
	color->b = ft_atoi_color(tab[2]);
	if (color->r < 0 || color->g < 0 || color->b < 0 || color->r > 255
		|| color->g > 255 || color->b > 255)
	{
		ft_putstr_fd("Error\nColor: must be 0 to 255\n", 2);
		free_split_tab(tab);
		free_tab(data);
		return (-1);
	}
	if (tab)
		free_split_tab(tab);
	return (0);
}
