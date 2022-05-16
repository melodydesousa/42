/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:42:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/09 16:18:24 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	i = 0;
	d = (unsigned int)c;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == d)
			return ((char *)&s[i]);
		else
			i--;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s1 = "bonjoujopjl";
	char	c1 = 'j';
	char	*s2 = "bonjoujopjl";
	char	c2 = 'j';

	printf("%s\n", strrchr(s1, c1));
	printf("%p\n", strrchr(s1, c1));
    printf("%s\n", ft_strrchr(s2, c2));
	printf("%p\n", ft_strrchr(s2, c2));
    return (0);
}
*/