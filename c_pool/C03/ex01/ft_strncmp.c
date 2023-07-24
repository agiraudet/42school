/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 16:32:11 by agiraude          #+#    #+#             */
/*   Updated: 2020/10/18 17:02:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	if (!n)
		return (0);
	while ((s1[i] && s1[i] == s2[i]) && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}
