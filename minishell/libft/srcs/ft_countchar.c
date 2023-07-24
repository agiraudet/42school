/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:57:54 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/02 23:26:09 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countchar(const char *s, char c)
{
	int		count;

	count = 0;
	if (!s)
		return (count);
	while (*s)
		if (*s++ == c)
			count++;
	return (count);
}
