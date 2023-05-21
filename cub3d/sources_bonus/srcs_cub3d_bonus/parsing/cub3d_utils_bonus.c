/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:45:17 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/05 11:59:34 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_tab(t_data *data)
{
	int	i;

	i = 0;
	printf("****************************INFOS***************************\n");
	if (data->tab)
	{
		while (data->tab[i] != NULL)
		{
			printf ("%s\n", data->tab[i]);
			i++;
		}
	}
	printf("\n\n\n\n");
}

void	print_tab_def(t_data *data)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = data->map.first_line;
	j = data->map.last_line;
	printf ("********************MAP DEF****************\n");
	if (data->tab)
	{
		while (i <= j)
		{
			printf ("%s\n", data->tab[i]);
			i++;
			k++;
		}
	}
}

char	*ft_dup_solong(char *s, int len)
{
	int		j;
	char	*dup;

	j = 0;
	dup = malloc(sizeof(char) * (len + 2));
	if (dup == NULL)
		return (0);
	while (s[j] && s[j] != '\n')
	{
		dup[j] = s[j];
		j++;
	}
	if (s[j] == '\n' || s[j] == '\0')
		dup[j] = '\0';
	return (dup);
}

void	ft_memset_cub3d(void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	if (s)
	{
		i = 0;
		str = s;
		while (i < n)
		{
			str[i] = c;
			i++;
		}
	}
}

int	ft_strlen_cub3d(char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i])
			i++;
	}
	return (i);
}
