/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:52:34 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/01 16:36:06 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file_in(const char *pathname)
{
	if (access(pathname, F_OK) != 0 || access(pathname, R_OK) != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(pathname);
		return (-1);
	}
	return (open(pathname, O_RDONLY));
}

int	open_file_out(const char *pathname)
{
	if (access(pathname, F_OK) == 0 && access(pathname, W_OK) != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(pathname);
		return (-1);
	}
	return (open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644));
}

int	usage(void)
{
	printf("pipex: wrongs arguments\n");
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	if ((argc != 5 && BONUS == 0) || argc < 5)
		return (usage());
	return (pipex(cmd_set(argc, argv, envp)));
}
