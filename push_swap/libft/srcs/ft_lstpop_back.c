/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:47:13 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/25 21:24:16 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstpop_back(t_list **lst)
{
	t_list	*pop;
	t_list	*prev;

	if (!*lst)
		return (0);
	pop = *lst;
	prev = 0;
	while (pop->next)
	{
		prev = pop;
		pop = pop->next;
	}
	if (prev)
		prev->next = 0;
	else
		*lst = 0;
	return (pop);
}
