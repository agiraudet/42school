/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:06:13 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/09 11:43:01 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_del(t_cmd *cmd)
{
	if (cmd->path)
		free(cmd->path);
	strlst_free(cmd->argv);
	free(cmd);
}

void	cmd_del_lst(t_cmd **cmd_lst)
{
	int	i;

	if (!cmd_lst)
		return ;
	i = 0;
	while (cmd_lst[i])
		cmd_del(cmd_lst[i++]);
	free(cmd_lst);
}

t_cmd	*cmd_create(const char *cmd_line, char **envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->argv = ft_split(cmd_line, ' ');
	cmd->envp = envp;
	cmd->path = path_for_cmd(cmd->argv[0], envp);
	cmd->pid = 0;
	if (cmd->path[0] != '.'
		&& ft_strchr(cmd->path, '/') == 0 && access(cmd->path, X_OK) != 0)
	{
		ft_putstr_fd(cmd->path, 2);
		ft_putendl_fd(":command not found", 2);
		free(cmd->path);
		cmd->path = 0;
		return (cmd);
	}
	return (cmd);
}

void	cmd_set_file(t_cmd *cmd, int i, int argc, char **argv)
{
	if (i == 0)
		cmd->file_in = argv[1];
	else
		cmd->file_in = 0;
	if (i == argc - 4)
		cmd->file_out = argv[argc - 1];
	else
		cmd->file_out = 0;
}

t_cmd	**cmd_set(int argc, char **argv, char **envp)
{
	t_cmd	**cmd_lst;
	int		i;

	cmd_lst = (t_cmd **)malloc(sizeof(t_cmd *) * (argc - 2));
	if (!cmd_lst)
		return (0);
	i = 0;
	while (i < argc - 3)
	{
		cmd_lst[i] = cmd_create(argv[i + 2], envp);
		cmd_set_file(cmd_lst[i], i, argc, argv);
		i++;
	}
	cmd_lst[i] = 0;
	return (cmd_lst);
}
