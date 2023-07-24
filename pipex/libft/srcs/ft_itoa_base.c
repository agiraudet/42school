/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:22:42 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/02 23:57:35 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *base)
{
	size_t	i;
	size_t	ii;

	if (!base)
		return (0);
	i = 0;
	while (base[i])
	{
		ii = 0;
		while (base[ii])
		{
			if (base[ii] == base[i] && i != ii)
				return (0);
			ii++;
		}
		i++;
	}
	if (i <= 1)
		return (0);
	return (1);
}

char	*ft_itoa_base(long nb, char *base)
{
	int		i;
	int		minus;
	long	baselen;
	char	buf[25];

	if (check_base(base) == 0)
		return (0);
	minus = 0;
	if (nb < 0)
	{
		minus = 1;
		nb *= -1;
	}
	baselen = ft_strlen(base);
	i = 0;
	while (nb >= baselen)
	{
		buf[i++] = base[nb % baselen];
		nb /= baselen;
	}
	buf[i++] = base[nb % baselen];
	if (minus)
		buf[i++] = '-';
	buf[i] = 0;
	return (ft_strdup(ft_revstr(buf)));
}
