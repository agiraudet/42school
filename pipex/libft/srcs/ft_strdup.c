/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:30:49 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/03 00:06:45 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *s)
{
	char	*d;

	d = dest;
	while (*s)
		*d++ = *s++;
	*d = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*ret;

	if (!s)
		return (0);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ret)
		return (0);
	return (ft_strcpy(ret, s));
}
