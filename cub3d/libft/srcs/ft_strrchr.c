/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:24:04 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/17 19:07:45 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*occurence;

	occurence = 0;
	while (*s)
	{
		if (*s == c)
			occurence = (char*)s;
		s++;
	}
	if (c == '\0')
		return ((char*)s);
	return (occurence);
}
