/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:42:52 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/07 16:31:13 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	pipe_setup_external(t_cmd *cmd)
{
	if (cmd->pipe_in)
	{
		dup2(cmd->pipe_in[0], STDIN_FILENO);
		close(cmd->pipe_in[1]);
		close(cmd->pipe_in[0]);
	}
	if (cmd->pipe_out)
	{
		dup2(cmd->pipe_out[1], STDOUT_FILENO);
		close(cmd->pipe_out[0]);
		close(cmd->pipe_out[1]);
	}
}

void	pipe_setup_builtin(t_cmd *cmd)
{
	if (cmd->rdrv[0])
		if (cmd->rdrv[0]->type == DOUBLE && cmd->rdrv[0]->dir == IN)
			return ;
	if (cmd->pipe_in)
		dup2(cmd->pipe_in[0], STDIN_FILENO);
	if (cmd->pipe_out)
		dup2(cmd->pipe_out[1], STDOUT_FILENO);
}

void	pipe_close(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	**pipe_newlist(int n)
{
	int	**pipe_lst;
	int	i;

	pipe_lst = (int **)calloc(n + 1, sizeof(int *));
	if (!pipe_lst)
		return (0);
	i = 0;
	while (i <= n)
	{
		if (i != 0 && i != n)
			pipe_lst[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	return (pipe_lst);
}

void	pipe_dellist(int **pipe_lst)
{
	int	i;

	i = 1;
	while (pipe_lst[i])
		free(pipe_lst[i++]);
	free(pipe_lst);
}
