/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:19:26 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/15 15:19:44 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim(const char *s)
{
	int		len;

	if (!s)
		return (0);
	while (ft_isspace(*s))
		s++;
	len = ft_strlen(s) - 1;
	while (ft_isspace(s[len]))
		len--;
	return (ft_substr(s, 0, ++len));
}
