/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:51:46 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 09:52:00 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_put(t_scene *sc)
{
	int y;
	int x;

	y = 0;
	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
			ft_putchar(sc->map.str[y * sc->map.size_x + x++]);
		ft_putchar('\n');
		y++;
	}
}

char	*map_correct_len(char *str, int old_len, int new_len, int nb_line)
{
	char	*new_str;
	int		i;
	int		j;
	int		line_count;

	new_str = malloc(sizeof(char) * (nb_line * new_len + 1));
	if (!new_str)
		return (0);
	line_count = 0;
	j = 0;
	while (line_count < nb_line)
	{
		i = 0;
		while (i < old_len)
			new_str[j++] = str[line_count * old_len + i++];
		while (i < new_len)
		{
			new_str[j++] = ' ';
			i++;
		}
		line_count++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*map_add_len(int new_len, const char *line)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char) * new_len + 1);
	i = 0;
	while (i < new_len)
	{
		if (*line)
			new_line[i++] = *line++;
		else
			new_line[i++] = ' ';
	}
	new_line[i] = '\0';
	return (new_line);
}

void	map_add(t_map *map, const char *line)
{
	static int	nb_line = 0;
	char		*tmp;
	int			len;

	len = ft_strlen(line);
	if (len > map->size_x)
	{
		if (nb_line > 0)
			map->str = map_correct_len(map->str, map->size_x, len, nb_line);
		map->size_x = len;
	}
	else if (len < map->size_x)
		line = map_add_len(map->size_x, line);
	tmp = map->str;
	map->str = ft_strjoin(tmp, line);
	free(tmp);
	map->size_y += 1;
	nb_line++;
}
