/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:40:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/06/29 10:42:57 by mede-sou         ###   ########.fr       */
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

//Gerer les arguments & erreurs
int		check_format_arg(char *s);
char	**ft_split(char const *s);
int		ft_atoi(char *s);
void   ft_doublon(t_list *a);

//Operations
//fonction qui print les instructions 

t_list	*ft_lstnew(int content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
// int		ft_lstsize(t_list *lst);

// void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list *lst, void (*del)(void*));
// void	ft_lstiter(t_list *lst, void (*f)(void *));
// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif