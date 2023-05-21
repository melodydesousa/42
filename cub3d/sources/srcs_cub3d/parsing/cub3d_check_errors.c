/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_check_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:58:32 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/10 11:57:19 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_if_doublon(char *str, char *check_str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == check_str[j])
		{
			if (ft_strnstr(str + i, check_str, 2) == 0)
				count += 1;
		}
		i++;
	}
	if (count > 1)
		return (-1);
	return (0);
}

int	check_if_tab(char *str, char **tab)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (tab[i])
	{
		if (ft_strnstr(tab[i], str, ft_strlen(str)) == 0)
		{
			if (check_if_doublon (tab[i], str) == -1)
				return (ft_putstr_fd("Error\nSame element\n", 2), -1);
			count += 1;
		}
		i++;
	}
	if (count == 0)
		return (ft_putstr_fd("Error\nMissing element\n", 2), -1);
	if (count > 1)
		return (ft_putstr_fd ("Error\nToo many elements\n", 2), -1);
	return (0);
}

int	check_all_path(t_data *data)
{
	int	check;

	check = 0;
	if (data->c.p && data->path.path_ea && data->f.p
		&& data->path.path_no && data->path.path_so && data->path.path_we)
			check = 1;
	return (check);
}

int	check_doublon_path(t_data *d)
{
	int		i;
	int		j;
	char	*tab[4];

	tab[0] = d->path.path_ea;
	tab[1] = d->path.path_no;
	tab[2] = d->path.path_so;
	tab[3] = d->path.path_we;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j <= 3)
		{
			if (i != j && ft_strcmp(tab[i], tab[j]) == 0)
				return (ft_putstr_fd("Error\nTextures are similar\n", 2),
					free_tab(d), -1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_tab_doublon(t_data *data)
{
	int	i;

	i = 0;
	init_check_tab(data);
	while (data->check_tab[i])
	{
		if (check_if_tab(data->check_tab[i], data->tab) == -1)
			return (free_tab(data), -1);
		if (save_path(data->check_tab[i], data) == -1)
			return (free_tab(data), -1);
		if (check_all_path(data) == 1)
		{
			if (save_last_info(data) == 1)
				break ;
		}
		i++;
	}
	if (check_doublon_path(data) == -1)
		return (-1);
	return (0);
}
