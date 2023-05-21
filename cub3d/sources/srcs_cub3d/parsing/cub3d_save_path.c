/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_save_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:11:29 by mede-sou          #+#    #+#             */
/*   Updated: 2023/01/06 10:33:29 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	make_we(char *str, t_data *data)
{
	if (make_path(str, "WE", data) == -1)
		return (-1);
	data->path.path_we = malloc(sizeof(char) * data->make_count + 1);
	if (data->path.path_we == NULL)
		return (-1);
	data->path.path_we = ft_strcpy_path(data->path.path_we,
			data->tab[data->make_i] + data->make_k);
	return (0);
}

int	make_ea(char *str, t_data *data)
{
	if (make_path(str, "EA", data) == -1)
		return (-1);
	data->path.path_ea = malloc(sizeof(char) * data->make_count + 1);
	if (data->path.path_ea == NULL)
		return (-1);
	data->path.path_ea = ft_strcpy_path(data->path.path_ea,
			data->tab[data->make_i] + data->make_k);
	return (0);
}

int	save_path_no_so_we(char *str, t_data *data)
{
	if (ft_strcmp(str, "NO") == 0)
	{
		if (make_path(str, "NO", data) == -1)
			return (-1);
		data->path.path_no = malloc(sizeof(char) * data->make_count + 1);
		if (data->path.path_no == NULL)
			return (-1);
		data->path.path_no = ft_strcpy_path(data->path.path_no,
				data->tab[data->make_i] + data->make_k);
	}
	else if (ft_strcmp(str, "SO") == 0)
	{	
		if (make_path(str, "SO", data) == -1)
			return (-1);
		data->path.path_so = malloc(sizeof(char) * data->make_count + 1);
		if (data->path.path_so == NULL)
			return (-1);
		data->path.path_so = ft_strcpy_path(data->path.path_so,
				data->tab[data->make_i] + data->make_k);
	}
	else if (ft_strcmp(str, "WE") == 0)
		return (make_we(str, data));
	return (0);
}

int	save_path_ea_c_f(char *str, t_data *data)
{
	if (ft_strcmp(str, "EA") == 0)
		return (make_ea(str, data));
	else if (ft_strcmp(str, "C") == 0)
	{
		if (make_path_color(str, "C", data, 0) == -1)
			return (-1);
		data->c.p = malloc(sizeof(char) * data->make_count + 1);
		if (data->c.p == NULL)
			return (-1);
		data->c.p = ft_strcpy_color(data->c.p,
				data->tab[data->make_i] + data->make_k);
	}
	else if (ft_strcmp(str, "F") == 0)
	{
		if (make_path_color(str, "F", data, 0) == -1)
			return (-1);
		data->f.p = malloc(sizeof(char) * data->make_count + 1);
		if (data->f.p == NULL)
			return (-1);
		data->f.p = ft_strcpy_color(data->f.p,
				data->tab[data->make_i] + data->make_k);
	}
	return (0);
}

int	save_path(char *str, t_data *data)
{
	if (ft_strcmp(str, "NO") == 0 || ft_strcmp(str, "SO") == 0
		|| ft_strcmp(str, "WE") == 0)
	{
		if (save_path_no_so_we(str, data) == -1)
			return (-1);
	}
	else if (ft_strcmp(str, "EA") == 0 || ft_strcmp(str, "C") == 0
		|| ft_strcmp(str, "F") == 0)
	{
		if (save_path_ea_c_f(str, data) == -1)
			return (-1);
	}
	return (0);
}
