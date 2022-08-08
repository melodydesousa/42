/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:16:44 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:21:05 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
int main ()
{
	printf("%d\n", ft_isprint(128));
	printf("%d\n", ft_isprint(2));
	printf("%d\n", ft_isprint('k'));
	printf("%d\n", ft_isprint(33));
}
*/
