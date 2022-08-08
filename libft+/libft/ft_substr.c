/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:03:14 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:22:04 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (start > ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (!s)
		return (NULL);
	if (len >= ft_strlen(s))
		str = malloc(ft_strlen(s + start) + 1);
	else
		str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (i < len && start < ft_strlen(s))
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int main ()
{
	char s1[] = "0123456789";
	printf("%s\n", ft_substr(s1, 9, 10));
	return (0);
}
*/