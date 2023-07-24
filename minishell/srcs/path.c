/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:03:07 by agiraude          #+#    #+#             */
/*   Updated: 2022/08/31 14:28:17 by mbenabbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

char	*path_try_all(char *cmdname, char **path_list)
{
	char	*pathname;
	int		i;

	pathname = NULL;
	if (!cmdname || !path_list)
		return (cmdname);
	i = 0;
	while (path_list[i])
	{
		pathname = ft_strjoin(path_list[i], cmdname);
		if (access(pathname, X_OK) == 0)
			break ;
		free(pathname);
		pathname = 0;
		i++;
	}
	if (path_list)
		ft_arrdel((void **)path_list, free);
	free(cmdname);
	return (pathname);
}

char	*path_set(t_cmd *cmd)
{
	char	*pathname;

	if (!cmd->argv[0])
		return (0);
	if (cmd->argv[0][0] == '.' || builtin_is(cmd->argv[0]))
		return (ft_strdup(cmd->argv[0]));
	pathname = path_try_all(ft_strjoin("/", cmd->argv[0]),
			ft_splitpath(env_get_value(cmd->lenvp, "PATH"), ':'));
	if (!pathname)
		return (ft_strdup(cmd->argv[0]));
	return (pathname);
}
