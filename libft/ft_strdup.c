/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:23:37 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/09 10:14:04 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dup;
	char	*src;

	src = (char *)s;
	i = 0;
	while (src[i])
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%s ; %s\n", strdup("bla"), ft_strdup("bla"));
	//printf("%p ; %p\n", strdup("bla"), ft_strdup("bla"));
    return (0);		
}   
*/