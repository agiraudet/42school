/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:57:17 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/01 14:02:15 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cursor;

	if (!lst)
		return ;
	while (*lst)
	{
		cursor = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = cursor;
	}
}
