/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_check_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:58:32 by amanasse          #+#    #+#             */
/*   Updated: 2022/12/20 16:06:24 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_argv(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	while (str[i] != '.' && i > 0)
		i--;
	if (str[i] == '.')
	{
		if (ft_strcmp (&str[i], ".cub\0") == 0)
			return (1);
		else
		{
			write (2, "Error\nthe map isn't a '.cub'\n", 29);
			return (0);
		}
	}
	write (2, "Error\nthe map isn't a '.cub'\n", 29);
	return (0);
}

void init_check_tab(t_data *data)
{
	data->check_tab[0] = "NO\0";
	data->check_tab[1] = "SO\0";
	data->check_tab[2] = "WE\0";
	data->check_tab[3] = "EA\0";
	data->check_tab[4] = "F\0";
	data->check_tab[5] = "C\0";
	data->check_tab[6] = NULL;
}

int check_if_doublon(char *str, char *check_str)
{
	int i;
	int j;
	int count;
	
	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == check_str[j])
		{
			if (ft_strnstr(str + i, check_str, 2) == 0)  
			{
				count += 1;
			}
		}
		i++;
	}
	if (count > 1)
		return (0);
	return (1);
}

int check_if_tab(char *str, char **tab)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (tab[i])
	{
		if (ft_strnstr(tab[i], str, 2) == 0)
		{
			if (check_if_doublon (tab[i], str) == 0)
			{
				printf("Error: too many %s\n", str);
				return (-1);
			}
			count += 1;
		}
		i++;
	}
	if (count == 0)
	{
		printf ("error: missing %s\n", str);
		return (-1);
	}
	if (count > 1)
	{
		printf ("error: too many %s\n", str);
		return (-1);
	}
	return (0);
}
int	save_path(char *str, t_data *data)
{
	int i;
	int j;
	int k;
	int count;
	
	count = 0;
	i = 0;
	j = 0;
	if (ft_strcmp(str, "NO") == 0)
	{
		while (data->tab[i])
		{
			if (ft_strnstr(data->tab[i], str, 2) == 0)
			{
				while (data->tab[i][j] == ' ' && data->tab[i][j] != '\0')
					j++;
				if (data->tab[i][j] == 'N')
					j++;
				if (data->tab[i][j] == 'O')
					j++;
				while (data->tab[i][j] == ' '&& data->tab[i][j] != '\0')
					j++;
				k = j;
				while (data->tab[i][j] != ' ' && data->tab[i][j] != '\0')
					j++;
				count = j - k;
				while (data->tab[i][j] == ' ' && data->tab[i][j] != '\0')
					j++;
				if (data->tab[i][j] != ' ' && data->tab[i][j] != '\0')
				{
					printf("Error: %s: Too many path\n", str);
					return (-1);
				}
				data->path_no = malloc(sizeof(char) * count + 1);
				data->path_no = ft_strcpy_path(data->path_no, data->tab[i] + k);
			}
			i++;
		}
		printf ("data->path_no = %s\n", data->path_no);
	}
	// else if (ft_strcmp(str, "SO") == 0)
	// {


		
	// }
	// else if (ft_strcmp(str, "WE") == 0)
	// {


		
	// }
	// else if (ft_strcmp(str, "EA") == 0)
	// {



		
	// }

	return (0);
}

int	check_tab_doublon (t_data *data)
{
	int i;

	i = 0;
	init_check_tab(data);
	// print_tab(data->check_tab);
	while (data->check_tab[i])
	{
		if (check_if_tab(data->check_tab[i], data->tab) == -1)
			return (0);
		if (save_path(data->check_tab[i], data) == -1)
			return (0);
		i++;   
	}
	return (1);
}