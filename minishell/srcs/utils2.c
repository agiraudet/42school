/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:06:05 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/11 11:25:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	ft_skip_quotes(const char *str, int *i)
{
	char	quote;

	quote = 0;
	if (str[*i] == '"' || str[*i] == '\'')
	{
		quote = str[*i];
		while (str[*i] && str[*i] != quote)
			(*i)++;
		(*i)++;
	}
}

int	ft_olen(char *src, char *find, char *replace, int *find_len)
{
	int	dst_len;
	int	replace_len;
	int	flag;

	dst_len = 0;
	flag = 1;
	if (!src || !find || !replace)
		return (0);
	*find_len = ft_strlen(find);
	replace_len = ft_strlen(replace);
	while (*src)
	{
		if (ft_strncmp(src, find, *find_len) == 0 && flag)
		{
			flag = 0;
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

void	ft_set_zero(int	*arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
		arr[i++] = 0;
}

char	*ft_strrplc_one(char *src, char *find, char *replace)
{
	char	*dst;
	int		find_len;
	int		i[3];

	dst = (char *)malloc(sizeof(char) * ft_olen(src, find, replace, &find_len));
	if (!dst)
		return (0);
	if (ft_strnstr(src, find, ft_strlen(src)) == 0 && ft_free(dst) == 0)
		return (ft_strdup(src));
	i[0] = 0;
	i[2] = 1;
	while (*src)
	{
		if (ft_strncmp(src, find, find_len) == 0 && i[2])
		{
			ft_set_zero(&i[1], 2);
			while (replace[i[1]])
				dst[i[0]++] = replace[i[1]++];
			src += find_len;
		}
		else
			dst[i[0]++] = *src++;
	}
	dst[i[0]] = 0;
	return (dst);
}
