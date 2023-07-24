/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:02:45 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/09 12:21:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_set_child(t_cmd *cmd, int *pfd)
{
	close(pfd[0]);
	if (cmd->file_out)
		close(pfd[1]);
	else
		dup2(pfd[1], STDOUT_FILENO);
}

int	pipex_child(t_cmd *cmd, t_cmd **cmd_lst)
{
	pid_t	pid;
	int		pfd[2];
	int		exit_code;

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		pipex_set_child(cmd, pfd);
		exit_code = 127;
		if (cmd->path)
		{
			execve(cmd->path, cmd->argv, cmd->envp);
			exit_code = errno;
		}
		cmd_del_lst(cmd_lst);
		exit(exit_code);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
	}
	return (pid);
}

pid_t	pipex_cmd(t_cmd *cmd, t_cmd **cmd_lst, int *err)
{
	int		ffd;

	if (cmd->file_in)
	{
		ffd = open_file_in(cmd->file_in);
		if (ffd < 0)
		{
			*err = -1;
			ffd = open("/dev/null", O_RDONLY);
		}
		dup2(ffd, STDIN_FILENO);
		close(ffd);
	}
	if (cmd->file_out)
	{
		ffd = open_file_out(cmd->file_out);
		if (ffd < 0)
		{
			*err = -2;
			ffd = open("/dev/null", O_RDWR);
		}
		dup2(ffd, STDOUT_FILENO);
		close(ffd);
	}
	return (pipex_child(cmd, cmd_lst));
}

int	pipex(t_cmd **cmd_lst)
{
	int		i;
	int		err;
	int		status;

	i = 0;
	err = 0;
	while (cmd_lst[i])
	{
		cmd_lst[i]->pid = pipex_cmd(cmd_lst[i], cmd_lst, &err);
		i++;
	}
	waitpid(cmd_lst[i - 1]->pid, &status, 0);
	cmd_del_lst(cmd_lst);
	if (err == -2)
		return (1);
	return (WEXITSTATUS(status));
}
