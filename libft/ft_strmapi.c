/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:10:49 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/16 17:49:07 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (s == 0 || f == 0)
		return (0);
	str = malloc(sizeof(char) * ft_strlen((char *)s) + 1);
	if (str == 0)
		return (0);
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

char test(unsigned int i, char c)
{
	return (c + i);
}

int main ()
{
	char s[] = "";

	printf("%s", ft_strmapi(s, &test));
	return (0);
}
*/