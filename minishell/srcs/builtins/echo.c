/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:04:32 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/06 12:05:54 by mbenabbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	only_n(char *str, int *n)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
		{
			*n = 1;
			return (0);
		}
		i++;
	}
	return (1);
}	

int	ft_echo(t_cmd *cmd)
{
	int	n;
	int	i;

	n = 1;
	i = 1;
	if (cmd->argv[i] && ft_strncmp("-n", cmd->argv[i], 2) == 0)
	{
		n = 0;
		while (cmd->argv[i]
			&& ft_strncmp("-n", cmd->argv[i], 2) == 0
			&& only_n(cmd->argv[i], &n))
			i++;
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i++]);
		if (cmd->argv[i])
			printf(" ");
	}
	if (n)
		printf("\n");
	return (0);
}
