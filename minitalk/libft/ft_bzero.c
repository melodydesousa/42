/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:42:58 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:52:08 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

/*
#include <stdio.h>
#include <string.h>
#include <stddef.h>

int main ()
{
	char str[] = "blablablablablabla";
	char str2[] = "blablablablablabla";
	int	tab[] = {0, 1, 2, 3};
	int	tab2[] = {0, 1, 2, 3};
	size_t	n = 3;

	bzero(str, n);
	printf("%s\n", str);
	printf("%c\n", str[7]);
	ft_bzero(str2, n);
	printf("%s\n", str2);
	printf("%c\n", str2[7]);
	bzero(tab, n);
	printf("%d\n", tab[0]);
	printf("%d\n", tab[1]);
	printf("%d\n", tab[2]);
	ft_bzero(tab2, n); 
    printf("%d\n", tab2[0]);
    printf("%d\n", tab2[1]);
    printf("%d\n", tab2[2]);
	return (0);
}
*/
