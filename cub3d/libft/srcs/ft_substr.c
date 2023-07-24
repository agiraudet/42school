/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:47:02 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/19 17:39:03 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	ret = (char*)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	i = 0;
	while (len-- && s[start])
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
