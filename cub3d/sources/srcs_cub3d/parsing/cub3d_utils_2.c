/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:20:45 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/05 18:19:37 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strcpy_path(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && src[i] != ' ')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy_map(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	dest[0] = 'X';
	while (i < (int)ft_strlen(src))
	{
		if (src[i] == ' ')
			dest[i + 1] = 'X';
		else
			dest[i + 1] = src[i];
		i++;
	}
	while (i <= len)
	{
		dest[i + 1] = 'X';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy_color(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	if (s1[i] == s2[i])
		return (0);
	else if (s1[i] < s2[i])
		return (-1);
	else
		return (1);
}
