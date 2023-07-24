/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:13:46 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/02 23:13:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arradd(void ***arr, void *new, size_t type_size)
{
	void	**new_arr;
	int		i;

	new_arr = (void **)calloc(ft_arrlen(*arr) + 2, sizeof(type_size));
	if (!new_arr)
		return ;
	i = 0;
	while ((*arr) && (*arr)[i])
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	new_arr[i] = new;
	if (*arr)
		free(*arr);
	*arr = new_arr;
}
