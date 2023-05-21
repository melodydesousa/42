/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:12:49 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:49:33 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_si_charset(const char *charset, char c)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		a;
	int		len;

	i = 0;
	a = 0;
	len = ft_strlen(s1);
	while (s1[i] && check_si_charset(set, s1[i]) == 1)
		i++;
	while (len > i && check_si_charset(set, s1[len - 1]) == 1)
	{
		a++;
		len--;
	}
	str = ft_substr(s1, i, (ft_strlen(s1 + i) - a));
	return (str);
}

/*
#include <stdio.h>
int main ()
{
	char s1[] = "+--+bal-+-blbal+-+-";
	char set[] = "+-";

	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}
*/