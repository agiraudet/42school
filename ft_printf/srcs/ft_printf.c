/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 19:12:01 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/15 16:04:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_printf(const char *str, ...)
{
	va_list	param;
	int		retnb;
	int		nbchar;

	va_start(param, str);
	nbchar = 0;
	while (*str != '\0')
	{
		if (*str != '%')
		{
			ft_putchar(*str++);
			nbchar++;
			continue ;
		}
		str++;
		retnb = elem_print(&str, &param);
		if (retnb == -1)
			return (-1);
		nbchar += retnb;
	}
	return (nbchar);
}
