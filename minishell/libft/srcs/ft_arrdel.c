/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:14:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/08/31 13:45:35 by mbenabbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrdel(void **arr, void (*del)(void *))
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != NULL)
		del(arr[i++]);
	free(arr);
}
