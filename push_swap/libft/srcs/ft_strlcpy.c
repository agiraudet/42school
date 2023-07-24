/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:35:19 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/25 20:50:48 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;

	if (!src)
		return (0);
	srclen = ft_strlen(src);
	if (!size)
		return (srclen);
	while (--size && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (srclen);
}
