/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:01:43 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/05 14:18:12 by mbenabbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	ft_cd(t_cmd *cmd)
{
	int	i;
	int	check;

	i = 0;
	while (cmd->argv[i])
		i++;
	if (i > 2)
	{
		error_msg("cd: to many arguments", BASIC);
		return (1);
	}
	if (!cmd->argv[1])
		check = chdir(env_get_value(cmd->lenvp, "HOME"));
	else
		check = chdir(cmd->argv[1]);
	if (check == -1)
	{
		printf("./mush: cd: %s:No such file or directory\n", cmd->argv[1]);
		return (1);
	}	
	env_update(&cmd->lenvp, "OLDPWD",
		ft_strdup(env_get_value(cmd->lenvp, "PWD")));
	env_update(&cmd->lenvp, "PWD", getcwd(0, 0));
	return (0);
}
