/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:15:14 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/10 17:43:39 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*str_src;
	char		*str_dest;
	size_t		i;

	str_dest = dest;
	str_src = src;
	i = 0;
	while (i < n)
	{
		str_dest[i] = str_src[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
   char str[] = "Geeksfor";
   memcpy(str+2, str, 5);
   printf("%s\n", str);
   ft_memcpy(str+2, str, 5);
   printf("%s\n", str);
   return 0;
}
*/
