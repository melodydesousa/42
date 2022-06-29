/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:40:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/06/28 14:17:59 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <strings.h>
# include <limits.h>

//struct

typedef struct s_stack 
{
  int		*a;
  int		*b;
  int		index_a;
  int		index_b;
  int		size;
} 					t_stack;

//Gerer les arguments & erreurs
int		check_nb_arg(char **av);
int		check_format_arg(char *s);
int		check_doublon(t_stack stack);
char	**ft_split(char const *s);
int		ft_atoi(char *s);
int		*ft_reverse_a(t_stack stack);
int		*ft_bzero(t_stack stack);

// int		*ft_make_a_split(char **tab, int i, int j);
// int		*ft_make_a_arg(char **av, int i, int ac);
// int		count_arg(int *a);

//Operations
void	ft_sa(t_stack stack);
void	ft_sb(t_stack stack);
void	ft_ss(t_stack stack);
void	ft_pa(t_stack stack);
void	ft_pb(t_stack stack);
//fonction qui print les instructions 

#endif