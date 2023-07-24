/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:11:42 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/10 14:25:57 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strinsert_fill(char *result, char *left, char *right, char *add)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (left[i])
		result[n++] = left[i++];
	i = 0;
	while (add[i])
		result[n++] = add[i++];
	i = 0;
	while (right[i])
		result[n++] = right[i++];
	result[n] = 0;
	return (result);
}

char	*ft_strinsert(char *src, int n, char *add)
{
	char	*left;
	char	*right;
	char	*result;

	left = ft_strndup(src, n);
	right = ft_strdup(&src[n]);
	result = (char *)malloc(sizeof(char *) * (ft_strlen(left)
				+ ft_strlen(right) + ft_strlen(add) + 1));
	if (!result)
	{
		free(left);
		free(right);
		return (0);
	}
	result = ft_strinsert_fill(result, left, right, add);
	free(left);
	free(right);
	return (result);
}
