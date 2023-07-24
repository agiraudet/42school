/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 03:07:40 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 16:14:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_str(const char *str, const char *sep)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] && ft_getindex(sep, str[i]) != -1)
		i++;
	while (str[i])
	{
		count++;
		while (str[i] && ft_getindex(sep, str[i]) == -1)
			i++;
		while (str[i] && ft_getindex(sep, str[i]) != -1)
			i++;
	}
	return (count);
}

static char	**destroy_ret(char **ret, int i)
{
	i--;
	while (i >= 0)
		free(ret[i--]);
	free(ret);
	return (0);
}

static char	**init_split(const char *str, const char *sep, int *i)
{
	char	**ret;

	if (!str)
		return (0);
	ret = malloc(sizeof(char *) * (count_str(str, sep) + 1));
	if (!ret)
		return (0);
	*i = 0;
	return (ret);
}

char	**ft_nsplit(const char *str, const char *sep)
{
	char	**ret;
	int		len;
	int		i;

	ret = init_split(str, sep, &i);
	if (!ret)
		return (0);
	while (*str)
	{
		while (*str && ft_getindex(sep, *str) != -1)
			str++;
		if (*str && ft_getindex(sep, *str) == -1)
		{
			len = 0;
			while (str[len] && ft_getindex(sep, str[len]) == -1)
				len++;
			ret[i] = ft_substr(str, 0, len);
			if (!ret[i])
				return (destroy_ret(ret, i + 1));
			i++;
			str += len;
		}
	}
	ret[i] = 0;
	return (ret);
}
