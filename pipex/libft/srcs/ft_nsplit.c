/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:15:00 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/03 01:11:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countstrs(char const *s, char const *sep)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && ft_getindex(sep, *s) != -1)
			s++;
		if (*s && ft_getindex(sep, *s) == -1)
		{
			count++;
			while (*s && ft_getindex(sep, *s) == -1)
				s++;
		}
	}
	return (count);
}

static char	**ft_free_tab(char ***tab, size_t i)
{
	i--;
	while (i > 0)
		free(*tab[i--]);
	free(*tab[i]);
	free(*tab);
	return (0);
}

int	ft_loop(char **dst, const char *s, const char *sep)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s && ft_getindex(sep, *s) != -1)
			s++;
		if (*s && ft_getindex(sep, *s) == -1)
		{
			len = 0;
			while (s[len] && ft_getindex(sep, s[len]) == -1)
				len++;
			dst[i] = ft_strndup(s, len);
			if (!dst[i])
			{
				ft_free_tab(&dst, i);
				return (0);
			}
			i++;
			s += len;
		}
	}
	dst[i] = 0;
	return (1);
}

char	**ft_nsplit(char const *s, char const *sep)
{
	char	**dst;

	if (!s)
		return (0);
	dst = (char **)malloc(sizeof(char *) * (ft_countstrs(s, sep) + 1));
	if (!dst)
		return (0);
	ft_loop(dst, s, sep);
	return (dst);
}
