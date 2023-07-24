/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:54:46 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/10 15:30:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	redir_heredoc(const char *limiter)
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

void	redir_out(t_redir *rdr)
{
	int	fd;

	if (rdr->type == SIMPLE)
		fd = open(rdr->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
	{
		if (access(rdr->word, F_OK) == -1)
			close(open(rdr->word, O_CREAT | O_RDWR | O_TRUNC, 0644));
		fd = open(rdr->word, O_CREAT | O_RDWR | O_APPEND);
	}
	if (fd < 0)
	{
		error_msg(rdr->word, STRNO);
		fd = open("/dev/null", O_RDWR);
	}
	if (rdr->fd != -1)
		dup2(fd, rdr->fd);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	redir_in(t_redir *rdr)
{
	int	fd;

	if (rdr->type == SIMPLE)
		fd = open(rdr->word, O_RDONLY);
	else
		fd = rdr->wip_fd;
	if (fd < 0)
	{
		error_msg(rdr->word, STRNO);
		fd = open("/dev/null", O_RDONLY);
	}
	return (fd);
}

void	redir_setup(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd->rdrv[i])
	{	
		if (cmd->rdrv[i]->dir == OUT)
			redir_out(cmd->rdrv[i]);
		else
		{
			fd = redir_in(cmd->rdrv[i]);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		i++;
	}
}
