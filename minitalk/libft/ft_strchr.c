/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:13:17 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:50:21 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	d;

	d = (unsigned int)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == d)
			return ((char *)&s[i]);
		i++;
	}
	if (d == 0)
		return ((char *)&s[i]);
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s1 = "testst";
	//char	c1 = '0';
	char	*s2 = "testst";
	//char	c2 = '0';

	printf("%p\n", strchr(s1, 0));
	//printf("%s\n", strchr(s1, c1));
    printf("%p\n", ft_strchr(s2, 0));
	//printf("%s\n", ft_strchr(s2, c2));
    return (0);
}
*/
