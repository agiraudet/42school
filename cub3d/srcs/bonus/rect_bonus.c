/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:14:48 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 15:18:25 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rect	rect_init(int x, int y, int wd, int hg)
{
	t_rect rect;

	rect.x = x;
	rect.y = y;
	rect.wd = wd;
	rect.hg = hg;
	return (rect);
}

void	rect_draw
	(t_scene *sc, t_rect rect, unsigned int color, int outline)
{
	int				x;
	int				y;
	unsigned int	draw_color;

	x = 0;
	y = 0;
	while (y < rect.hg)
	{
		x = 0;
		while (x < rect.wd)
		{
			if ((outline != -1) &&
					(x == 0 || y == 0 || y == rect.hg - 1 || x == rect.wd - 1))
				draw_color = outline;
			else
				draw_color = color;
			pixel_put_buffer(sc, rect.x + x, rect.y + y, draw_color);
			x++;
		}
		y++;
	}
}
