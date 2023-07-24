/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:40:40 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/03 00:09:36 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	if (!(*needle))
		return ((char *)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (needle[i] && haystack[i] == needle[i])
				i++;
			if (needle[i] == 0)
				return ((char *)haystack);
		}
		haystack++;
	}
	return (0);
}
