/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:29:12 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/08 17:53:07 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	builtin_ft(t_cmd *cmd)
{
	if (!cmd->argv[0])
		return (0);
	if (strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd));
	if (strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd));
	if (strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd());
	if (strcmp(cmd->argv[0], "exit") == 0)
		return (ft_exit(cmd));
	if (strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(cmd));
	if (strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd));
	if (strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd));
	return (-1);
}

int	builtin_is(const char *cmdname)
{
	char	**builtin_lst;
	int		i;
	int		ret;

	if (!cmdname)
		return (1);
	ret = 0;
	builtin_lst = ft_split(BUILTIN_LIST, ' ');
	i = 0;
	while (builtin_lst[i])
	{
		if (ft_strcmp(cmdname, builtin_lst[i]) == 0)
		{
			ret = 1;
			break ;
		}
		i++;
	}
	ft_arrdel((void **)builtin_lst, free);
	return (ret);
}
