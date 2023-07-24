/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:42:21 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 17:52:40 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_BONUS_H
# define LIBASM_BONUS_H

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

int					ft_atoi_base(const char *s, const char *base);
void				ft_list_push_front(t_list **list, void *data);
int					ft_list_size(t_list *list);
void				ft_list_sort(t_list **begin_list, int (*cmp)());
void				ft_list_remove_if
(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void*));

t_list				*ft_create_elem(void *data);
void				ft_list_delone(t_list *elem, void (*free_fct)(void*));

#endif
