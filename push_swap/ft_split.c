/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:28:13 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/03 15:31:49 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_arg(const char *s)
{
	int	i;
	int	count;
	int	word;

	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			word = 0;
		else if (s[i] != ' ' && word == 0)
		{
			word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static int	len_word(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ')
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

static char	**ft_free_split(int size, char **strs)
{
	while (size > 0)
	{
		size--;
		free(strs[size]);
	}
	return (NULL);
}

char	**ft_split(char const *s)
{
	int		i;
	int		j;
	int		size;
	char	**strs;

	i = 0;
	j = 0;
	size = count_arg(s);
	strs = malloc(sizeof(char **) * (size + 1));
	if (strs == NULL)
		return (0);
	while (s[i] && j < size)
	{
		while (s[i] == ' ')
			i++;
		strs[j] = ft_dup((char *)(s + i), len_word((char *)(s + i)));
		if (strs[j] == NULL)
			return (ft_free_split(size, strs));
		i = i + len_word((char *)(s + i));
		j++;
	}
	strs[j] = 0;
	return (strs);
}
