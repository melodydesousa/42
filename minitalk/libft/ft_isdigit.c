/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:38:59 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:51:48 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>

int		main()
{
	printf("%s\n%s\n%s\n%s\n%s\n",
			ft_isdigit("")?"OK":"Fail",
			!ft_isdigit("ABCDqrstuvwxyz")?"OK":"Fail",
			ft_isdigit("0123456789")?"OK":"Fail",
			!ft_isdigit(" ")?"OK":"Fail",
			!ft_isdigit("\n")?"OK":"Fail");
}
*/
