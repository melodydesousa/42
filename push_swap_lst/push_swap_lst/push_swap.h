/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:40:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/11 16:13:32 by mede-sou         ###   ########.fr       */
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
typedef struct s_list
{
	int				content;
	struct s_list	*next;
	int				size;
}					t_list;

typedef struct s_ope 
{
  	int	count;
} 					t_ope;

//Gerer les arguments & erreurs
int		check_format_arg(char *s);
char	**ft_split(char const *s);
int		ft_atoi(char *s);
void	ft_doublon(t_list *a);

//Operations
void	ft_sa(t_list *a, t_ope ope);
void	ft_sb(t_list *b, t_ope ope);
void	ft_ss(t_list *a, t_list *b, t_ope ope);
void	ft_pa(t_list **a, t_list **b, t_ope ope);
void	ft_pb(t_list **b, t_list **a, t_ope ope);
int		pop(t_list **pile);
void 	push(t_list **pile, int content);
void	ft_ra(t_list **a, t_ope ope);
void	ft_rb(t_list **b, t_ope ope);
void	ft_rr(t_list **a, t_list **b, t_ope ope);
void	ft_rra(t_list **a, t_ope ope);
void	ft_rrb(t_list **b, t_ope ope);
void	ft_rrr(t_list **a, t_list **b, t_ope ope);

//fonction qui print les instructions 

//Construire piles
t_list	*ft_lstnew(int content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_make_a_split(t_list **a, char **av);
void	ft_make_a_av(t_list **a, char **av);
// void	ft_lstdelone(t_list *lst, void (*del)(void*));
// void	ft_lstclear(t_list *lst, void (*del)(void*));
// void	ft_lstiter(t_list *lst, void (*f)(void *));
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//Calculs
void	init_push_swap(t_list **a);
void	push_swap_2(t_list *a, t_ope ope);
void	push_swap_3(t_list **a, t_ope ope);
void	push_swap_4_5(t_list **a, t_ope ope);

int	find_max(t_list *a, int size);

void	make_b(t_list **a, int size, t_ope ope);

#endif