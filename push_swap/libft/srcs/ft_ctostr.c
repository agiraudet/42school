/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 15:49:05 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 10:41:55 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_ctostr(int c)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * 2);
	if (!ret)
		return (0);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}
