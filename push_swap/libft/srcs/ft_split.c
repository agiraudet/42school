/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:15:00 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 16:19:41 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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

static char	*ft_cutstr(char const *s, size_t len)
{
	char	*ret;
	size_t	i;

	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	i = 0;
	while (len-- && *s)
		ret[i++] = *s++;
	ret[i] = '\0';
	return (ret);
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

static char	**ft_init_split(char const *s, char c, size_t *i)
{
	char	**ret;

	if (!s)
		return (0);
	ret = (char **)malloc(sizeof(char *) * (ft_countstrs(s, c) + 1));
	if (!ret)
		return (0);
	*i = 0;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	len;
	size_t	i;

	ret = ft_init_split(s, c, &i);
	if (!ret)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			ret[i] = ft_cutstr(s, len);
			if (!ret[i])
				return (ft_free_tab(&ret, i + 1));
			i++;
			s += len;
		}
	}
	ret[i] = 0;
	return (ret);
}
