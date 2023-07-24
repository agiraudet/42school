/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:00:59 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/10 15:47:13 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	signal_handle_sigint(int sig, siginfo_t *info, void *ucontext)
{
	int	i;

	i = 0;
	if (ucontext && sig && i)
		i = 1;
	if (info->si_pid != 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_code_set(130);
	}
}

void	signals_set(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sigemptyset(&(sig_int.sa_mask));
	sigemptyset(&(sig_quit.sa_mask));
	sigaddset(&(sig_int.sa_mask), SIGINT);
	sigaddset(&(sig_quit.sa_mask), SIGINT);
	sig_quit.sa_flags = SA_NODEFER;
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_quit, 0);
	sig_int.sa_flags = SA_SIGINFO;
	sig_int.sa_sigaction = signal_handle_sigint;
	sigaction(SIGINT, &sig_int, 0);
}

void	signal_handle_sigint_bis(int sig, siginfo_t *info, void *ucontext)
{
	int	i;

	i = 0;
	if (sig && ucontext && i)
		i = 1;
	if (info->si_pid != -1 && sig == SIGINT)
		exit_code_set(130);
	if (info->si_pid != -1 && sig == SIGQUIT)
		exit_code_set(131);
}

void	signals_set_bis(void)
{
	struct sigaction	sig_quit;
	struct sigaction	sig_int;

	sigemptyset(&(sig_int.sa_mask));
	sigemptyset(&(sig_quit.sa_mask));
	sigaddset(&(sig_int.sa_mask), SIGINT);
	sigaddset(&(sig_quit.sa_mask), SIGQUIT);
	sig_quit.sa_flags = SA_NODEFER;
	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_sigaction = signal_handle_sigint_bis;
	sigaction(SIGQUIT, &sig_quit, 0);
	sig_int.sa_flags = SA_SIGINFO;
	sig_int.sa_sigaction = signal_handle_sigint_bis;
	sigaction(SIGINT, &sig_int, 0);
}

pid_t	signal_check_in_pipe(void)
{
	pid_t	pid;
	int		extern_status;
	int		flag;

	flag = 0;
	while (1)
	{
		pid = waitpid(-1, &extern_status, 0);
		if (pid == -1)
			break ;
		else if (WIFSIGNALED(extern_status)
			&& WTERMSIG(extern_status) == 2 && !flag)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			flag = 1;
		}
	}
	return (pid);
}
