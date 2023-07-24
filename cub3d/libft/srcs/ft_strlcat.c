/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:14:38 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/16 16:57:40 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t dstlen;

	dstlen = ft_strlen(dst);
	i = 0;
	if (dstlen < size)
	{
		while (src[i] && (i + dstlen + 1) < size)
		{
			dst[dstlen + i] = src[i];
			i++;
		}
	}
	if (size > 0 && dstlen <= size)
		dst[i + dstlen] = '\0';
	if (dstlen < size)
		return (dstlen + ft_strlen(src));
	else
		return (size + ft_strlen(src));
}
