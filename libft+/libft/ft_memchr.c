/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 10:06:02 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:22:48 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*str;
	size_t				i;
	unsigned char		d;

	str = s;
	d = (unsigned char)c;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (str[i] == d)
			return ((unsigned char *)&str[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s1 = "teststl";
	char s[] = {0, 1, 2 ,3 ,4 ,5};
	char	c1 = 'l';
	char	*s2 = "teststl";
	char	c2 = 'l';
    size_t  n = 3;

	printf("%p\n", memchr(s, 2 + 256, sizeof(char)*n));
	printf("%p\n", ft_memchr(s, 2 + 256, sizeof(char)*n));
	printf("%p\n", memchr(s1, c1, sizeof(char)*n));
    printf("%p\n", ft_memchr(s2, c2, sizeof(char)*n));
    return (0);
}
*/