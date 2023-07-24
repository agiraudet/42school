/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:22:42 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 16:15:22 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	check_error(char *base, long baselen)
{
	size_t	i;
	size_t	ii;

	if (baselen <= 1)
		return (0);
	i = 0;
	while (base[i])
	{
		ii = 0;
		while (base[ii])
		{
			if (base[i] == base[ii] && i != ii)
				return (0);
			ii++;
		}
		i++;
	}
	return (1);
}

static int	choose_sign(long nb)
{
	if (nb < 0)
		return (-1);
	else
		return (1);
}

static long	ft_abs(long nb)
{
	if (nb < 0)
		return (nb * -1);
	else
		return (nb);
}

char	*ft_itoa_base(long nb, char *base)
{
	char	tmp[100];
	char	*ret;
	int		sign;
	long	baselen;
	size_t	i;

	baselen = ft_strlen(base);
	if (check_error(base, baselen) == 0)
		return (0);
	sign = choose_sign(nb);
	nb = ft_abs(nb);
	i = 0;
	while (nb >= baselen)
	{
		tmp[i++] = base[nb % baselen];
		nb /= baselen;
	}
	tmp[i++] = base[nb % baselen];
	if (sign == -1)
		tmp[i++] = '-';
	tmp[i] = '\0';
	ret = ft_strdup(tmp);
	if (!ret)
		return (0);
	return (ft_revstr(ret));
}
