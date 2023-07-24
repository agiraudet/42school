/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrflst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:14:13 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/02 23:14:21 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_arrflst(t_list	**lst, size_t type_size)
{
	void	**arr;
	t_list	*elem;
	size_t	len;
	size_t	i;

	len = ft_lstlen(*lst);
	arr = (void **)calloc(len + 1, type_size);
	if (!arr)
		return (0);
	i = 0;
	while (i < len)
	{
		elem = ft_lstpop_front(lst);
		arr[i++] = elem->content;
		free(elem);
	}
	return (arr);
}
