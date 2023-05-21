/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:28:13 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:50:24 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_si_charset(char d, char c)
{
	if (d == c)
		return (1);
	return (0);
}

static int	count_arg(char *s, char c)
{
	int	i;
	int	count;
	int	word;

	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (check_si_charset(s[i], c) == 1)
			word = 0;
		else if (check_si_charset(s[i], c) == 0 && word == 0)
		{
			word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int	len_word(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && check_si_charset(s[i], c) == 0)
		i++;
	return (i);
}

static char	*ft_dup(char *s, int len)
{
	int		j;
	char	*dup;

	j = 0;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (0);
	while (s[j] && j < len)
	{
		dup[j] = s[j];
		j++;
	}
	dup[j] = 0;
	return (dup);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		size;
	char	**strs;

	i = 0;
	j = 0;
	size = count_arg((char *)s, c);
	strs = malloc(sizeof(char **) * (size + 1));
	if (strs == NULL)
		return (0);
	while (s[i] && j < size)
	{
		while (check_si_charset(s[i], c) == 1)
			i++;
		if (check_si_charset(s[i], c) == 0)
		{
			strs[j] = ft_dup((char *)(s + i), len_word((char *)(s + i), c));
			i = i + len_word((char *)(s + i), c);
			j++;
		}
	}
	strs[j] = 0;
	return (strs);
}
/*
#include <stdio.h>
int	main(void)
{
	char	**tab;

	tab = ft_split("+Ceci++-est+++un+test", '+');
	printf("%s\n", tab[0]);
	free(tab[0]);
	printf("%s\n", tab[1]);
	free(tab[1]);
	printf("%s\n", tab[2]);
	free(tab[2]);
	printf("%s\n", tab[3]);
	free(tab[3]);
	free(tab);
}
*/