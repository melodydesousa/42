/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_remake_map2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:28:49 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/06 09:42:30 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**make_new_tab2(t_data *data, int first, int last)
{
	char	**tab;
	int		i;
	int		k;

	k = 0;
	i = 0;
	tab = malloc(sizeof(char *) * (last - first + 4));
	if (tab == NULL)
		return (free_tab(data), NULL);
	tab[0] = malloc(sizeof(char) * data->map.largest_line + 3);
	if (tab[0] == NULL)
		return (free_tab(data), NULL);
	while (i < data->map.largest_line + 1)
	{
		tab[0][k] = 'X';
		i++;
		k++;
	}
	tab[0][k] = '\0';
	return (tab);
}

char	*make_last_line(char *str, t_data *data)
{
	int	k;

	k = 0;
	while (k < data->map.largest_line + 1)
	{
		str[k] = 'X';
		k++;
	}
	str[k] = '\0';
	return (str);
}

char	**make_new_tab3(char **tab, t_data *data, int first, int last)
{
	int		i;
	char	*tmp;

	i = 1;
	while (first <= last)
	{
		tmp = malloc(sizeof(char) * data->map.largest_line + 3);
		if (tmp == NULL)
			return (free_tab(data), NULL);
		tmp = ft_strcpy_color(tmp, data->tab[first]);
		tab[i] = tmp;
		i++;
		first++;
	}
	tab[i] = malloc(sizeof(char) * data->map.largest_line + 3);
	if (tab[i] == NULL)
		return (free_tab(data), NULL);
	tab[i] = make_last_line(tab[i], data);
	tab[++i] = NULL;
	return (tab);
}

int	correct_map(t_data *data, int first, int last)
{
	char	**tab;
	int		i;

	tab = make_new_tab2(data, first, last);
	if (tab == NULL)
		return (-1);
	tab = make_new_tab3(tab, data, first, last);
	if (tab == NULL)
		return (-1);
	i = 0;
	while (data->tab[i])
	{
		free(data->tab[i]);
		i++;
	}
	free(data->tab);
	data->tab = tab;
	return (0);
}

int	remake_map2(t_data *data)
{
	int	j;

	j = count_largest_line(data);
	if (new_map(data, j) == -1)
		return (free_tab(data), -1);
	if (check_borders(data, data->map.first_line, data->map.last_line, 0) == -1)
		return (free_tab(data), -1);
	if (correct_map(data, data->map.first_line, data->map.last_line) == -1)
		return (free_tab(data), -1);
	if (check_zero(data) == -1)
		return (free_tab(data), -1);
	return (0);
}
