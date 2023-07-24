/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:57:17 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/18 15:43:00 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
