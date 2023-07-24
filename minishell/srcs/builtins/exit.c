/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:05:18 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/10 16:02:45 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	ft_exit_check(t_cmd *cmd)
{
	int	argc;
	int	i;

	ft_putendl_fd("exit", STDOUT_FILENO);
	argc = ft_arrlen((void **)cmd->argv);
	if (argc > 2)
	{
		error_msg("exit", NB_ARG);
		return (0);
	}
	if (argc > 1)
	{
		i = 0;
		while (cmd->argv[1][i])
		{
			if (!ft_isdigit(cmd->argv[1][i++]))
			{
				error_msg(cmd->argv[1], EXIT_ARG);
				return (1);
			}
		}
	}
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	int	code;

	code = 0;
	if (cmd->argv[1])
	{
		code = ft_atoi(cmd->argv[1]);
		if (code > 255)
			code %= 255;
	}
	return (code);
}
