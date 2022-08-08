/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:11:37 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:18:34 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_line(char *save, int nb_octets);
char	*ft_save(char **stock, int nb_octets);
int		ft_strlen(char *s);
char	*ft_malloc(int len);
char	*ft_strjoin(char *s1, char *s2);
int		check_sep(char *save, int octets_lus);
char	*ft_temp_join(char *save, char *dest);

#endif