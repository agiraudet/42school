/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:31:53 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/09 11:38:12 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	strlst_free(char **strlst)
{
	int	i;

	i = 0;
	while (strlst[i])
		free(strlst[i++]);
	free(strlst);
}

char	**path_from_env(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (ft_split(&(*envp)[5], ':'));
		envp++;
	}
	return (0);
}

char	*path_try_all(char *cmd_name, char **path_list)
{
	char	*pathname;
	int		i;

	i = 0;
	while (path_list[i])
	{
		pathname = ft_strjoin(path_list[i], cmd_name);
		if (access(pathname, X_OK) == 0)
		{
			strlst_free(path_list);
			free(cmd_name);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	strlst_free(path_list);
	free(cmd_name);
	return (0);
}

char	*path_for_cmd(char *cmd_name, char **envp)
{
	char	*cmd_path;

	if (cmd_name[0] == '.')
		return (ft_strdup(cmd_name));
	else
	{
		cmd_path = path_try_all(ft_strjoin("/", cmd_name), path_from_env(envp));
		if (cmd_path)
			return (cmd_path);
		return (ft_strdup(cmd_name));
	}
}
