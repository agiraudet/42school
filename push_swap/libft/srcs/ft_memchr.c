/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:00:28 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 10:43:09 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cursor;

	cursor = (unsigned char *)s;
	while (n--)
	{
		if (*cursor == (unsigned char)c)
			return (cursor);
		cursor++;
	}
	return (0);
}
