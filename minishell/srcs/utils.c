/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:23:28 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/11 11:14:24 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	ft_stdfd(int mode)
{
	static int	stdfd[3];

	if (mode == 0)
	{
		stdfd[0] = dup(STDIN_FILENO);
		stdfd[1] = dup(STDOUT_FILENO);
		stdfd[2] = dup(STDERR_FILENO);
	}
	else if (mode == 1)
	{
		dup2(stdfd[0], STDIN_FILENO);
		dup2(stdfd[1], STDOUT_FILENO);
		dup2(stdfd[2], STDERR_FILENO);
	}
	else if (mode == 2)
	{
		close(stdfd[0]);
		close(stdfd[1]);
		close(stdfd[2]);
	}
}

void	ft_str_substitute(char **src, char *find, char *replace)
{
	char	*tmp;	

	tmp = ft_strrplc_one(*src, find, replace);
	free(*src);
	*src = tmp;
}

int	ft_isdir(const char *pathname)
{
	struct stat	statbuf;

	if (stat(pathname, &statbuf) != 0)
		return (0);
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

int	ft_issain(const char *str)
{
	if (!str || (*str == 0 || (!ft_isalpha(*str) && *str != '_')))
		return (0);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	check_rdr(char *str)
{
	size_t	i;
	int		in_space;

	i = 0;
	while (i < ft_strlen(str))
	{
		in_space = 0;
		if (str[i] == '>' || str[i] == '<')
		{
			i++;
			if (str[i] && str[i] == str[i - 1])
				i++;
			if (ft_isspace(str[i]))
				in_space = 1;
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (!str[i])
				return (0);
			if (in_space == 1
				&& (!str[i] || str[i] == '>' || str[i] == '<'))
				return (0);
		}
		i++;
	}
	return (1);
}
