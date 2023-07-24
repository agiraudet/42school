/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:52:08 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/03 00:10:07 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(const char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

static size_t	ft_countch(const char *s1, const char *set)
{
	size_t	count;

	count = 0;
	while (*s1 && ft_inset(*s1, set))
		s1++;
	if (!(*s1))
		return (0);
	while (*s1)
	{
		count++;
		s1++;
	}
	s1--;
	while (ft_inset(*s1, set))
	{
		count--;
		s1--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	size;
	size_t	i;

	if (!s1 || !set)
		return (0);
	size = ft_countch(s1, set);
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (0);
	while (ft_inset(*s1, set))
		s1++;
	i = 0;
	while (size--)
		ret[i++] = *s1++;
	ret[i] = '\0';
	return (ret);
}
