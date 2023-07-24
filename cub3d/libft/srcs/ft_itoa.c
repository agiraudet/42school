/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:47:04 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/21 17:10:28 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	ft_intlen(int nb)
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

char			*ft_itoa(int n)
{
	char	*str;
	int		neg;
	size_t	i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = n < 0 ? 1 : 0;
	n = n < 0 ? n * -1 : n;
	str = (char*)malloc(sizeof(char) * (ft_intlen(n) + 1 + neg));
	if (!str)
		return (0);
	i = 0;
	while (n > 9)
	{
		str[i++] = n % 10 + '0';
		n /= 10;
	}
	str[i++] = n + '0';
	if (neg)
		str[i++] = '-';
	str[i] = '\0';
	ft_revstr(str);
	return (str);
}
