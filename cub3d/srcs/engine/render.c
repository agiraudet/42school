/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 23:17:19 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 20:45:28 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ceil_render(t_scene *sc, int x, t_ray *ray)
{
	int y;

	y = 0;
	while (y < ray->draw_start)
		pixel_put_buffer(sc, x, y++, sc->set.color_c);
}

void	floor_render(t_scene *sc, int x, t_ray *ray)
{
	int y;

	y = ray->draw_end;
	while (y < sc->set.proj.hg)
		pixel_put_buffer(sc, x, y++, sc->set.color_f);
}

int		strip_get_tex_x(t_scene *sc, t_tex *tex, t_ray *ray)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0 || ray->side == 1)
		wall_x = sc->plr.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = sc->plr.pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)tex->wd);
	if ((ray->side == 0 || ray->side == 1) && ray->dir_x > 0)
		tex_x = tex->wd - tex_x - 1;
	if ((ray->side == 2 || ray->side == 3) && ray->dir_y < 0)
		tex_x = tex->wd - tex_x - 1;
	return (tex_x);
}

void	strip_render(t_scene *sc, int x, t_ray *ray)
{
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
	t_tex	*tex;

	tex = &sc->texs[ray->side];
	tex_x = strip_get_tex_x(sc, tex, ray);
	step = 1.0 * tex->hg / ray->line_hg;
	tex_pos = (ray->draw_start - sc->set.proj.half_hg
			+ ray->line_hg / 2) * step;
	while (ray->draw_start < ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->hg - 1);
		tex_pos += step;
		pixel_put_buffer(sc, x, ray->draw_start++,
				tex_get_color(tex, tex_x, tex_y));
	}
}

void	ray_draw(t_scene *sc, t_ray *ray, int x)
{
	ray->draw_start = ceil((double)-ray->line_hg / 2.0
			+ (double)sc->set.proj.hg / 2.0);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ceil((double)ray->line_hg / 2.0
			+ (double)sc->set.proj.hg / 2.0);
	if (ray->draw_end >= sc->set.proj.hg)
		ray->draw_end = sc->set.proj.hg;
	if (BONUS)
		skybox_render(sc, x, ray);
	else
		ceil_render(sc, x, ray);
	strip_render(sc, x, ray);
	if (!BONUS)
		floor_render(sc, x, ray);
}
