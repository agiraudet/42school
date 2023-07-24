/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:22:21 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/02 23:22:28 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dst;

	if (!src || n <= 0)
		return (0);
	if (ft_strlen(src) <= n)
		return (ft_strdup(src));
	dst = (char *)malloc(sizeof(char) * (n + 1));
	if (!dst)
		return (0);
	ft_strlcpy(dst, src, n + 1);
	return (dst);
}
