/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:31:25 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/18 12:54:41 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = (t_list*)malloc(sizeof(t_list));
	if (!elem)
		return (0);
	elem->content = content;
	elem->next = 0;
	return (elem);
}
