/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 19:20:41 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/17 12:36:04 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_error(int fd, char **line, char **buffer)
{
	if (fd < 0 || !line || 256 < 1)
		return (0);
	*buffer = (char *)malloc(sizeof(char) * (256 + 1));
	if (!(*buffer))
		return (0);
	return (1);
}

int	end_of_file(int rd, int keepgoing, char **content)
{
	if (!rd && !keepgoing)
	{
		if (*content)
		{
			free(*content);
			*content = 0;
		}
		return (0);
	}
	return (1);
}

int	get_next_line_2(char **content, int	*keepgoing, char **line, int rd)
{
	if (!(*content))
	{
		*keepgoing = 0;
		*line = ft_strdup("");
	}
	else
	{
		*keepgoing = get_first_line(line, content);
		if (*keepgoing == -1)
			return (-1);
	}
	return (end_of_file(rd, *keepgoing, content));
}

int	get_next_line(int fd, char **line)
{
	static char	*content = 0;
	char		*buffer;
	int			rd;
	int			keepgoing;

	rd = 1;
	if (!check_error(fd, line, &buffer))
		return (-1);
	while (getnl(content) == -1)
	{
		rd = read(fd, buffer, 256);
		if (rd <= 0)
			break ;
		buffer[rd] = '\0';
		rd = clean_join(&content, buffer);
	}
	free(buffer);
	if (rd == -1)
		return (-1);
	return (get_next_line_2(&content, &keepgoing, line, rd));
}
