/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 15:49:05 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/02 23:26:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
