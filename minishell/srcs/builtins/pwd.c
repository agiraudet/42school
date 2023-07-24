/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:02:18 by agiraude          #+#    #+#             */
/*   Updated: 2022/08/30 14:20:11 by mbenabbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
	{
		printf("something is wrong with the path\n");
		return (errno);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
