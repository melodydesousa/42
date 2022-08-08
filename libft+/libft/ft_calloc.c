/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 09:19:30 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:21:12 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	if (nmemb != 0 && size != 0)
	{
		if (nmemb * size / size != nmemb)
			return (NULL);
	}
	s = malloc(sizeof(void) * (nmemb * size));
	if (s == NULL)
		return (NULL);
	while (i < (nmemb * size))
	{
		s[i] = '\0';
		i++;
	}
	return (s);
}
/*
#include <stdlib.h>
#include <stdio.h>

int main ()
{
    size_t nmemb = __SIZE_MAX__ / 2 + 1;
    size_t size = __SIZE_MAX__ / 2 + 1;

    printf("%p : %p\n", calloc(nmemb, size), ft_calloc(nmemb, size));
    return (0);
}
*/