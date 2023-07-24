/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrplc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:21:40 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/03 01:46:13 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrplc(char *src, char *find, char *replace)
{
	size_t	dst_len;
	char	*dst;
	char	*dst_ptr;
	char	*find_ptr;

	find_ptr = ft_strnstr(src, find, ft_strlen(src));
	if (!find_ptr)
		return (ft_strdup(src));
	dst_len = (ft_strlen(src) - ft_strlen(find) + ft_strlen(replace) + 1);
	dst = (char *)malloc(sizeof(char) * dst_len);
	if (!dst)
		return (0);
	*dst = 0;
	dst_ptr = dst;
	while (*src)
	{
		if (ft_strncmp(src, find, ft_strlen(find)) == 0)
		{
			*dst_ptr = 0;
			ft_strlcat(dst_ptr, replace, dst_len);
			src += ft_strlen(find);
			dst_ptr += ft_strlen(replace);
		}
		else
			*dst_ptr++ = *src++;
	}
	*dst_ptr = 0;
	return (dst);
}
