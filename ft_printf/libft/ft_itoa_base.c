/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:22:42 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/08 10:34:08 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char		*ft_itoa_base(unsigned long long nb, char *base)
{
	char				tmp[100];
	char				*ret;
	unsigned long long	baselen;
	size_t				i;

	baselen = ft_strlen(base);
	if (check_error(base, baselen) == 0)
		return (0);
	i = 0;
	while (nb >= baselen)
	{
		tmp[i++] = base[nb % baselen];
		nb /= baselen;
	}
	tmp[i++] = base[nb % baselen];
	tmp[i] = '\0';
	ret = ft_strdup(tmp);
	if (!ret)
		return (0);
	return (ft_revstr(ret));
}
