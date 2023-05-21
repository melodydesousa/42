/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:23:38 by mede-sou          #+#    #+#             */
/*   Updated: 2022/09/29 11:57:33 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <sys/types.h>
# include "libft/libft.h"
# include "libft/printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"

# define BUFFER 8

void	ft_make_str(char *str, char c);
char	binary_to_char(char *str);
char	*ft_make_stock(char *stock_str, char c);
void	make_c(int signum, char *str, char *stock_str);
void	signal_handler(int signum);

#endif