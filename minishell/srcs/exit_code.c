/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:01:37 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/10 15:47:31 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	exit_code(int *code)
{
	static int	exit_code = 0;

	if (!code)
		return (exit_code);
	else
		exit_code = *code;
	return (0);
}

void	exit_code_set(int code)
{
	exit_code(&code);
}

int	exit_code_get(void)
{
	return (exit_code(0));
}

void	exit_code_retrieve(pid_t pid, pid_t last_pid, int extern_status,
							int *exit_code)
{
	if (pid == last_pid)
	{
		if (WIFEXITED(extern_status))
			*exit_code = WEXITSTATUS(extern_status);
		else if (WIFSIGNALED(extern_status))
		{
			if (WTERMSIG(extern_status) == 2)
			{
				ft_putstr_fd("\n", STDOUT_FILENO);
				*exit_code = 130;
			}
			else if (WTERMSIG(extern_status) == 3)
			{
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				*exit_code = 131;
			}
		}
	}
}

int	exit_code_from_cmd(int builtin_status, pid_t last_pid)
{
	int		extern_status;
	int		exit_code;
	pid_t	pid;

	exit_code = 0;
	while (1)
	{
		pid = waitpid(last_pid, &extern_status, 0);
		if (last_pid == -1)
			exit_code = builtin_status;
		else
		{
			exit_code_retrieve(pid, last_pid, extern_status, &exit_code);
			pid = signal_check_in_pipe();
		}
		if (pid == -1)
			break ;
	}
	return (exit_code);
}
