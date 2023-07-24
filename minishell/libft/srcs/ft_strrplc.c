/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrplc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:21:40 by agiraude          #+#    #+#             */
/*   Updated: 2022/06/27 13:30:21 by mbenabbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getlen(char *src, char *find, char *replace, int *find_len)
{
	int	dst_len;
	int	replace_len;

	if (!src || !find || !replace)
		return (0);
	dst_len = 0;
	*find_len = ft_strlen(find);
	replace_len = ft_strlen(replace);
	while (*src)
	{
		if (ft_strncmp(src, find, *find_len) == 0)
		{
			dst_len += replace_len;
			src += *find_len;
		}
		else
		{
			dst_len++;
			src++;
		}
	}
	return (dst_len + 1);
}

int	ft_free(char *str)
{
	free(str);
	str = NULL;
	return (0);
}

char	*ft_strrplc(char *src, char *find, char *replace)
{
	char	*dst;
	int		find_len;
	int		i;
	int		ii;

	dst = (char *)malloc(sizeof(char) * getlen(src, find, replace, &find_len));
	if (!dst)
		return (0);
	if (ft_strnstr(src, find, ft_strlen(src)) == 0 && ft_free(dst) == 0)
		return (ft_strdup(src));
	i = 0;
	while (*src)
	{
		if (ft_strncmp(src, find, find_len) == 0)
		{
			ii = 0;
			while (replace[ii])
				dst[i++] = replace[ii++];
			src += find_len;
		}
		else
			dst[i++] = *src++;
	}
	dst[i] = 0;
	return (dst);
}
