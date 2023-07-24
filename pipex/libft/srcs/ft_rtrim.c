/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtrim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:20:27 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/15 15:20:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_rtrim(const char *s)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	i = ft_strlen(s) - 1;
	while (ft_isspace(s[i]))
		i--;
	return (ft_substr(s, 0, ++i));
}
