/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:25:55 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/09 12:53:17 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i])
	{
		if (i < size - 1)
		{
			dst[i] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (i);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int main()
{
    char dest[] = "1234";
    char src[] = "ABCD";
    size_t size = 0;
    
    ft_strlcpy(dest, src, size);
    printf("%s\n", dest);
    printf("%d\n", ft_strlcpy(dest, src, size));
    strlcpy(dest, src, size);
    printf("%s\n", dest);
    printf("%ld\n", strlcpy(dest, src, size));
    return(0);
}
*/