/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:42:49 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/25 21:51:04 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstswap(t_list *prev, t_list *a)
{
	t_list	*tmp;

	if (!a || !(a->next) || !prev)
		return ;
	tmp = a->next->next;
	prev->next = a->next;
	a->next->next = a;
	a->next = tmp;
}
