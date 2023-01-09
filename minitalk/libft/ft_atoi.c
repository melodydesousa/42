/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:23:14 by mede-sou          #+#    #+#             */
/*   Updated: 2022/09/28 14:15:04 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (ft_str_is_numeric((char *)(nptr + i)) == 0)
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + (nptr[i] - 48);
		i++;
	}
	return (n);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d:%d\n", atoi("  \n  42t4457"), ft_atoi("  \n  42t4457"));
	printf("%d:%d\n", atoi("42sfs:f545"), ft_atoi(" +42sfs:f545"));
	printf("%d:%d\n", atoi("\0 1337"), ft_atoi("\0 1337"));
	printf("%d:%d\n", atoi("-0"), ft_atoi("-0"));
	printf("%d:%d\n", atoi(" - 1 3 2 5 6 3 2 1 6 7"), 
                        ft_atoi(" - 1 3 2 5 6 3 2 1 6 7"));
	printf("%d:%d\n", atoi("-100"), ft_atoi("-100"));
	printf("%d:%d\n", atoi("\t-2147483648"), ft_atoi("\t-2147483648"));
	printf("%d:%d\n", atoi("\v2147483647"), ft_atoi("\v2147483647"));
}
*/
