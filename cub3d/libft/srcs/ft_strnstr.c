/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:40:40 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/19 17:51:25 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!(*little))
		return ((char*)big);
	while (*big && len > 0)
	{
		if (*big == *little)
		{
			i = 0;
			while (little[i] && big[i] == little[i] && i < len)
				i++;
			if (little[i] == '\0')
				return ((char*)big);
		}
		big++;
		len--;
	}
	return (0);
}
