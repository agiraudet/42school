/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:42:31 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/07 17:10:03 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*arg_to_str(char *arg)
{
	if (!arg)
	{
		return (ft_strdup("(null)"));
	}
	return (arg);
}

char	*arg_to_ptr(unsigned long long ptr)
{
	if (!ptr)
		return (ft_strdup("0"));
	return (ft_itoa_base(ptr, "0123456789abcdef"));
}

char	*arg_to_chr(t_elem *e, wchar_t x)
{
	if (x == 0 || x > 255)
	{
		e->zero_flag = 1;
		e->wchar = x;
		x = '.';
	}
	return (ft_ctostr(x));
}

char	*fix_hex(char *src)
{
	int		i;

	i = 0;
	while (src[i] == '0')
		i++;
	if (i == 1)
		return (src);
	else if (src[i] == 'x')
	{
		src[i] = '0';
		src[1] = 'x';
	}
	return (src);
}

void	fix_minus(char *src)
{
	int		i;

	i = 0;
	while (src[i] == '0')
		i++;
	if (src[i] == '-')
	{
		src[i] = '0';
		src[0] = '-';
	}
}
