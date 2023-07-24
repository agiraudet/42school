/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:14:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/02 23:14:45 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrsort(void **tab, int (*cmp)(void *, void *))
{
	int		i;
	char	*tmp;

	if (!tab || !tab[0] || !tab[1])
		return ;
	i = 1;
	while (tab[i])
	{
		if ((*cmp)(tab[i - 1], tab[i]) > 0)
		{
			tmp = tab[i - 1];
			tab[i - 1] = tab[i];
			tab[i] = tmp;
			i = 0;
		}
		i++;
	}
}
