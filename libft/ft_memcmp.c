/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:51:14 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/09 11:01:09 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*str1;
	unsigned const char	*str2;

	str1 = s1;
	str2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		else
			i++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char s1[] = "123";
	int	tab1[] = {0, 1, 2, 3};
	int	tab2[] = {0, 1, 2, 3};
	char s3[] = "";
	char s4[] = "";
	char s5[] = "Shorter";
	char s7[] = "ShorterTest";

	
	printf("%d, %d\n", ft_memcmp(tab1, tab2, 8), memcmp(tab1, tab2, 8));
	printf("%d, %d\n", ft_memcmp(s1, s3, 8), memcmp(s1, s3, 3));
	printf("%d, %d\n", ft_memcmp(s3, s4, 4), memcmp(s3, s4, 0));
	printf("%d, %d\n", ft_memcmp(s5, s7, 15), memcmp(s5, s7, 15));
    return (0);
}
*/