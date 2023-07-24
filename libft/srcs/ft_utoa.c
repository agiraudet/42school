/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 15:40:29 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/03 00:15:38 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_ulen(unsigned int nb)
{
	size_t	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_utoa(unsigned int n)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * (ft_ulen(n) + 1));
	if (!str)
		return (0);
	i = 0;
	while (n > 9)
	{
		str[i++] = n % 10 + '0';
		n /= 10;
	}
	str[i++] = n + '0';
	str[i] = '\0';
	ft_revstr(str);
	return (str);
}
