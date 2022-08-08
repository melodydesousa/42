/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:42:48 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:21:53 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lendest;
	size_t	lensrc;

	i = 0;
	j = 0;
	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	j = lendest + lensrc;
	if (size <= lendest)
		return (lensrc + size);
	while (src[i] && lendest + i < size - 1)
	{
		dest[lendest + i] = src[i];
		i++;
	}
	dest[lendest + i] = '\0';
	return (j);
}
/*
#include <bsd/string.h>
#include <stdio.h>

int main()
{
    size_t t = 1;
    char dest[30]; memset(dest, 0, 30);    
    char src[] = "123";
    dest[0] = 'B';
    ft_strlcat(dest, src, t);
    printf("%s\n", dest);
    printf("%ld\n", ft_strlcat(dest, src, t));
    strlcat(dest, src, t);
    printf("%s\n", dest);
    printf("%ld\n", strlcat(dest, src, t));
    return(0);
}
*/