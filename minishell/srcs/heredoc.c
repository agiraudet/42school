/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:36:45 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/08 11:25:05 by mbenabbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	heredoc_close(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->rdrv[i])
	{
		if (cmd->rdrv[i]->type == DOUBLE && cmd->rdrv[i]->dir == IN)
			close(cmd->rdrv[i]->wip_fd);
		i++;
	}
}

int	heredoc_check(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->rdrv[i])
	{
		if (cmd->rdrv[i]->dir == IN && cmd->rdrv[i]->type == DOUBLE)
		{
			cmd->rdrv[i]->wip_fd = heredoc(cmd->rdrv[i]->word);
		}
		i++;
	}
	return (0);
}

int	heredoc(const char *limiter)
{
	int		pfd[2];
	char	*line;

	pipe(pfd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			error_msg((char *)limiter, LIMIT);
			break ;
		}
		if (ft_strcmp(line, limiter) == 0)
			break ;
		ft_putendl_fd(line, pfd[1]);
		free(line);
	}
	if (line)
		free(line);
	close(pfd[1]);
	return (pfd[0]);
}
