/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:15:00 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/03 01:07:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countstrs(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
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

int	ft_loop(char **dst, const char *s, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			len = 0;
			while (s[len] && s[len] != c)
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

char	**ft_split(char const *s, char c)
{
	char	**dst;

	if (!s)
		return (0);
	dst = (char **)malloc(sizeof(char *) * (ft_countstrs(s, c) + 1));
	if (!dst)
		return (0);
	if (!ft_loop(dst, s, c))
		return (0);
	return (dst);
}
