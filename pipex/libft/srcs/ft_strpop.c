/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:19:10 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/15 16:28:54 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpop(char **arr, const char *str)
{
	int		i;
	int		ii;
	char	*ret;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], str) == 0)
		{
			ret = arr[i];
			ii = 1;
			while (arr[i + ii])
			{
				arr[i + ii - 1] = arr[i + ii];
				ii++;
			}
			arr[i + ii - 1] = 0;
			return (ret);
		}
		i++;
	}
	return (0);
}
