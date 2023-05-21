/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:35:56 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:42:40 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *save, char *dest)
{
	char	*new_save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_save = malloc (ft_strlen_gnl(save) + ft_strlen_gnl(dest) + 1);
	if (new_save == NULL)
		return (NULL);
	while (save && save[i])
	{
		new_save[i] = save[i];
		i++;
	}
	while (dest[j])
	{
		new_save[i + j] = dest[j];
		j++;
	}
	new_save[i + j] = '\0';
	return (new_save);
}

char	*ft_temp_join(char *save, char *dest)
{
	char		*new_save;

	new_save = save;
	new_save = ft_strjoin_gnl(save, dest);
	free(save);
	save = NULL;
	return (new_save);
}
