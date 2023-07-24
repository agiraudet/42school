/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:11:48 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/10 15:38:38 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	exec_clean(t_cmd **cmd_lst_ptr, int **pipe_lst_ptr)
{
	static t_cmd	**cmd_lst = 0;
	static int		**pipe_lst = 0;

	if (!cmd_lst_ptr && ! pipe_lst_ptr)
	{
		if (cmd_lst)
			ft_arrdel((void **)cmd_lst, cmd_del);
		if (pipe_lst)
			pipe_dellist(pipe_lst);
	}
	else
	{
		cmd_lst = cmd_lst_ptr;
		pipe_lst = pipe_lst_ptr;
	}
}

int	exec_external(t_cmd *cmd)
{
	heredoc_check(cmd);
	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		signals_set_bis();
		pipe_setup_external(cmd);
		redir_setup(cmd);
		execve(cmd->pathname, cmd->argv, cmd->envp);
		error_msg(cmd->argv[0], NOCMD);
		exit_clean(cmd->lenvp);
		exec_clean(0, 0);
		exit(127);
	}
	else if (cmd->pipe_in)
		pipe_close(cmd->pipe_in);
	heredoc_close(cmd);
	return (0);
}

int	exec_builtin(t_cmd *cmd)
{
	int	status;

	heredoc_check(cmd);
	ft_stdfd(0);
	pipe_setup_builtin(cmd);
	redir_setup(cmd);
	status = builtin_ft(cmd);
	if (cmd->pipe_in)
		pipe_close(cmd->pipe_in);
	ft_stdfd(1);
	ft_stdfd(2);
	return (status);
}

int	exec_cmd(t_cmd **cmd_lst, int **pipe_lst, int i)
{
	if (pipe_lst[i + 1])
		pipe(pipe_lst[i + 1]);
	cmd_lst[i]->pipe_in = pipe_lst[i];
	cmd_lst[i]->pipe_out = pipe_lst[i + 1];
	if (builtin_is(cmd_lst[i]->argv[0]))
		return (exec_builtin(cmd_lst[i]));
	else
		return (exec_external(cmd_lst[i]));
}

int	exec_cmdlst(t_cmd **cmd_lst)
{
	int	**pipe_lst;
	int	exec_status;
	int	status;
	int	i;

	if (!cmd_lst || !cmd_lst[0])
		return (1);
	pipe_lst = pipe_newlist(ft_arrlen((void **)cmd_lst));
	if (!pipe_lst)
		return (0);
	exec_clean(cmd_lst, pipe_lst);
	i = 0;
	while (cmd_lst[i])
		exec_status = exec_cmd(cmd_lst, pipe_lst, i++);
	exit_code_set(exit_code_from_cmd(exec_status, cmd_lst[i - 1]->pid));
	status = 1;
	if (cmd_lst[0]->argv[0] && ft_strcmp(cmd_lst[0]->argv[0], "exit") == 0
		&& !cmd_lst[1] && ft_exit_check(cmd_lst[0]))
		status = 0;
	exec_clean(0, 0);
	return (status);
}
