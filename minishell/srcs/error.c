/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:02:54 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/10 16:01:50 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

char	*error_name(char *name)
{
	static char	*prog_name = 0;

	if (name)
		prog_name = name;
	return (prog_name);
}

int	error_msg3(char *msg, enum e_err mode)
{
	if (mode == EXIT_ARG)
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit_code_set(2);
	}
	else if (mode == NB_ARG)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		exit_code_set(1);
	}
	else if (mode == AMB_REDIR)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
		exit_code_set(1);
	}
	return (0);
}

int	error_msg2(char *msg, enum e_err mode)
{
	if (mode == BASIC)
		ft_putendl_fd(msg, STDERR_FILENO);
	else if (mode == TOKEN)
	{
		exit_code_set(2);
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		free(msg);
	}
	else if (mode == HANDLE)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd("not supposed to handle that", STDERR_FILENO);
	}
	else if (mode == EXPORT)
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putendl_fd("': not a valid indentifier", STDERR_FILENO);
	}
	else
		return (error_msg3(msg, mode));
	return (0);
}

int	error_msg(char *msg, enum e_err mode)
{
	ft_putstr_fd(error_name(0), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (mode == NOCMD)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd("command not found", STDERR_FILENO);
	}
	else if (mode == LIMIT)
	{
		ft_putstr_fd(
			"warning: here-document delimited by end-of-file (wanted `",
			STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
	}
	else if (mode == STRNO)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
		return (error_msg2(msg, mode));
	return (0);
}
