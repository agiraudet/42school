/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:48:26 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 15:18:34 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skybox_render(t_scene *sc, int x, t_ray *ray)
{
	int		offset;
	double	angle;
	int		tex_x;
	double	tex_y;
	int		y;

	angle = atan2(ray->dir_y, ray->dir_x);
	offset = fix_angle(angle * 180 / M_PI);
	tex_y = (double)sc->texs[TEX_BG].hg / (double)sc->set.proj.half_hg;
	y = 0;
	while (y < ray->draw_start)
	{
		tex_x = sc->texs[TEX_BG].wd / 360 * offset;
		pixel_put_buffer(sc, x, y,
				tex_get_color(&sc->texs[TEX_BG], tex_x, y * tex_y));
		y++;
	}
}

void	ground_next_stripe(t_floor *floor)
{
	floor->cell_x = (int)(floor->x);
	floor->cell_y = (int)(floor->y);
	floor->tex_x = (int)(floor->tex->wd *
			(floor->x - floor->cell_x)) & (floor->tex->wd - 1);
	floor->tex_y = (int)(floor->tex->hg *
			(floor->y - floor->cell_y)) & (floor->tex->hg - 1);
	floor->x += floor->step_x;
	floor->y += floor->step_y;
}

void	ground_set_stripe(t_scene *sc, t_floor *floor, int y)
{
	floor->ray_dir_x0 = sc->plr.dir_x - sc->plr.plan_x;
	floor->ray_dir_y0 = sc->plr.dir_y - sc->plr.plan_y;
	floor->ray_dir_x1 = sc->plr.dir_x + sc->plr.plan_x;
	floor->ray_dir_y1 = sc->plr.dir_y + sc->plr.plan_y;
	floor->p = y - sc->set.proj.half_hg;
	floor->pos_z = 0.5 * sc->set.proj.hg;
	floor->row_dist = floor->pos_z / floor->p;
	floor->step_x = floor->row_dist *
		(floor->ray_dir_x1 - floor->ray_dir_x0) / sc->set.proj.wd;
	floor->step_y = floor->row_dist *
		(floor->ray_dir_y1 - floor->ray_dir_y0) / sc->set.proj.wd;
	floor->x = sc->plr.pos_x + floor->row_dist * floor->ray_dir_x0;
	floor->y = sc->plr.pos_y + floor->row_dist * floor->ray_dir_y0;
}

void	ground_render(t_scene *sc)
{
	t_floor	floor;
	int		x;
	int		y;

	floor.tex = &sc->texs[TEX_F];
	y = sc->set.proj.half_hg;
	while (y < sc->set.proj.hg)
	{
		ground_set_stripe(sc, &floor, y);
		x = 0;
		while (x < sc->set.proj.wd)
		{
			ground_next_stripe(&floor);
			pixel_put_buffer(sc, x, y,
					tex_get_color(floor.tex, floor.tex_x, floor.tex_y));
			x++;
		}
		y++;
	}
}
