/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:58:20 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 16:46:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			minimap_init(t_scene *sc)
{
	int	mini_size;
	int	mini_offset;

	mini_size = sc->set.proj.wd / 40;
	mini_offset = mini_size >> 4;
	sc->mini.size = mini_size / PROJ_SCALE;
	sc->mini.x = mini_offset / PROJ_SCALE;
	sc->mini.y = mini_offset / PROJ_SCALE;
	sc->mini.show = MINI_SHOW;
}

unsigned int	minimap_get_color(t_scene *sc, int x, int y)
{
	unsigned int	color;

	if (ft_strchr("0NEWS", sc->map.str[y * sc->map.size_x + x]))
		color = LIGHT_GRAY;
	else if (sc->map.str[y * sc->map.size_x + x] == '1')
		color = 0;
	else if (sc->map.str[y * sc->map.size_x + x] == '2')
		color = GREEN;
	else
		color = 0;
	return (color);
}

void			minimap_draw(t_scene *sc)
{
	t_rect			tile;
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
		{
			if ((color = minimap_get_color(sc, x, y)))
			{
				tile = rect_init(x * sc->mini.size + sc->mini.x,
				y * sc->mini.size + sc->mini.y, sc->mini.size, sc->mini.size);
				rect_draw(sc, tile, color, -1);
			}
			x++;
		}
		y++;
	}
	tile = rect_init(sc->plr.pos_x * sc->mini.size + sc->mini.x - 1,
	(sc->plr.pos_y * sc->mini.size + sc->mini.y) - 1,
	sc->mini.size - 1, sc->mini.size - 1);
	rect_draw(sc, tile, YELLOW, -1);
}
