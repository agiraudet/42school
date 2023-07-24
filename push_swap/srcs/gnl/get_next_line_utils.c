/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:23:56 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/17 12:43:44 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	getnl(const char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	slen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	clean_join(char **cont, char *buf)
{
	char	*new_cont;
	int		i;

	new_cont = (char *)malloc(sizeof(char) * (slen(*cont) + slen(buf) + 1));
	if (!new_cont)
	{
		if (*cont)
			free(*cont);
		return (-1);
	}
	i = 0;
	while (*cont && (*cont)[i])
	{
		new_cont[i] = (*cont)[i];
		i++;
	}
	while (*buf)
		new_cont[i++] = *buf++;
	new_cont[i] = '\0';
	if (*cont)
		free(*cont);
	*cont = new_cont;
	return (1);
}

int	set_end(char **cont, int i)
{
	char	*new_cont;
	int		end;

	end = 0;
	if ((*cont)[i] == '\n')
		end = 1;
	if ((*cont)[i] == '\n')
		i++;
	new_cont = ft_strdup(*cont + i);
	if (!new_cont)
		end = -1;
	if (*cont)
		free(*cont);
	*cont = 0;
	if (end > -1)
		*cont = new_cont;
	return (end);
}

int	get_first_line(char **line, char **cont)
{
	int		i;

	*line = (char *)malloc(sizeof(char) * (slen(*cont) + 2));
	if (!(*line))
	{
		free(*cont);
		return (-1);
	}
	i = 0;
	while ((*cont)[i] && (*cont)[i] != '\n')
	{
		(*line)[i] = (*cont)[i];
		i++;
	}
	(*line)[i] = '\0';
	return (set_end(cont, i));
}
