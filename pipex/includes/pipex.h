/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:04:48 by agiraude          #+#    #+#             */
/*   Updated: 2022/02/09 12:52:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"

# define BONUS 0

typedef struct s_cmd
{
	char	*path;
	char	**argv;
	char	**envp;
	char	*file_in;
	char	*file_out;
	pid_t	pid;
}				t_cmd;

void	cmd_del_lst(t_cmd **lst);
t_cmd	**cmd_set(int argc, char **argv, char **envp);
int		open_file_in(const char *pathname);
int		open_file_out(const char *pathname);
int		*open_file(int argc, char **argv);
void	strlst_free(char **strlst);
char	*path_for_cmd(char *cmd_name, char **envp);
int		pipex(t_cmd **cmd_lst);

#endif
