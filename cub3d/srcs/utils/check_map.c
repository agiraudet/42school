/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:27:14 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/22 12:53:15 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_around(t_scene *sc, int y, int x, int *start_pos)
{
	int around_y;
	int	around_x;

	if (ft_strchr("NSEW", sc->map.str[y * sc->map.size_x + x]))
		*start_pos = 1;
	around_y = (y > 0) ? y - 1 : 0;
	while (around_y <= y + 1)
	{
		around_x = (x > 0) ? x - 1 : 0;
		while (around_x <= x + 1)
		{
			if (around_y != y || around_x != x)
				if (!(ft_strchr("012NSEW",
						sc->map.str[around_y * sc->map.size_x + around_x])))
					return (0);
			around_x++;
		}
		around_y++;
	}
	return (1);
}

int		check_map_valid(t_scene *sc)
{
	int		y;
	int		x;
	int		start_pos;
	char	*map;

	start_pos = 0;
	map = sc->map.str;
	y = 0;
	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
		{
			if (ft_strchr("0NSEW2", map[y * sc->map.size_x + x]))
				if (check_around(sc, y, x, &start_pos) == 0)
					return (0);
			x++;
		}
		y++;
	}
	if (!start_pos)
		return (-1);
	return (1);
}

int		check_extension(char *file)
{
	int		i;

	i = ft_strlen(file);
	i -= 4;
	file += i;
	if (ft_strncmp(file, ".cub", 4) != 0)
	{
		error_set(FILE_ERROR, "wrong type");
		return (0);
	}
	return (1);
}

int		check_map(t_scene *sc)
{
	int		check;

	check = check_map_valid(sc);
	if (check == -1)
	{
		error_set(FILE_ERROR, "no player position");
		return (0);
	}
	else if (check == 0)
	{
		error_set(FILE_ERROR, "map not closed");
		return (0);
	}
	return (1);
}

void	proj_set(t_scene *sc)
{
	sc->set.proj.scale = PROJ_SCALE;
	sc->set.proj.wd = sc->set.win_x / PROJ_SCALE;
	sc->set.proj.hg = sc->set.win_y / PROJ_SCALE;
	sc->set.proj.half_wd = sc->set.proj.wd / 2;
	sc->set.proj.half_hg = sc->set.proj.hg / 2;
}
