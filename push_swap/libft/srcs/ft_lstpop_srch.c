/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_srch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 21:42:59 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/23 15:21:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstpop_srch(t_list **lst, int (*f)(void *, void *), void *data)
{
	t_list	*pop;
	t_list	*prev;

	if (!*lst)
		return (0);
	pop = *lst;
	prev = 0;
	while (!f(pop->content, data))
	{
		if (!pop->next)
			break ;
		prev = pop;
		pop = pop->next;
	}
	if (prev)
		prev->next = pop->next;
	else
		*lst = pop->next;
	return (pop);
}
