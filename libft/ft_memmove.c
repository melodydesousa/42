/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:15:14 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/16 16:23:31 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*str_src;
	char		*str_dest;
	size_t		i;

	str_dest = dest;
	str_src = src;
	i = 0;
	if (str_src < str_dest)
	{
		while (n > 0)
		{
			n--;
			str_dest[n] = str_src[n];
		}
	}
	else
	{
		while (i < n)
		{
			str_dest[i] = str_src[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main()
{
   char str[] = "abcde";
   ft_memmove(str+5, str, 2);
   printf("%s\n", str);
   memmove(str+5, str, 2);
   printf("%s\n", str);
   return 0;
}
*/
