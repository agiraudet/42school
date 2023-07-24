/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 00:52:30 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/23 16:52:19 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop_front(t_list **lst)
{
	t_list	*pop;

	if (!lst || !*lst)
		return (0);
	pop = *lst;
	*lst = (*lst)->next;
	return (pop);
}
