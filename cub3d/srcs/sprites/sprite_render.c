/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 19:05:45 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/18 01:14:50 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spt_set_data(t_scene *sc, t_spt_render *spt, int i)
{
	spt->x = sc->spt.buf[i].x - sc->plr.pos_x;
	spt->y = sc->spt.buf[i].y - sc->plr.pos_y;
	spt->inv_det = 1.0 /
		(sc->plr.plan_x * sc->plr.dir_y - sc->plr.dir_x * sc->plr.plan_y);
	spt->tsfm_x = spt->inv_det
		* (sc->plr.dir_y * spt->x - sc->plr.dir_x * spt->y);
	spt->tsfm_y = spt->inv_det
		* (-sc->plr.plan_y * spt->x + sc->plr.plan_x * spt->y);
	spt->screen_x = (int)(sc->set.proj.half_wd
			* (1 + spt->tsfm_x / spt->tsfm_y));
	spt->hg = abs((int)(sc->set.proj.hg / spt->tsfm_y));
	spt->draw_start_y = sc->set.proj.half_hg - spt->hg / 2;
	if (spt->draw_start_y < 0)
		spt->draw_start_y = 0;
	spt->draw_end_y = sc->set.proj.half_hg + spt->hg / 2;
	if (spt->draw_end_y >= sc->set.proj.hg)
		spt->draw_end_y = sc->set.proj.hg - 1;
	spt->wd = abs((int)(sc->set.proj.hg / spt->tsfm_y));
	spt->draw_start_x = -spt->wd / 2 + spt->screen_x;
	if (spt->draw_start_x < 0)
		spt->draw_start_x = 0;
	spt->draw_end_x = spt->wd / 2 + spt->screen_x;
	if (spt->draw_end_x >= sc->set.proj.wd)
		spt->draw_end_x = sc->set.proj.wd - 1;
}

void	spt_put_pixel(t_scene *sc, t_spt_render *spt, int x, int y)
{
	unsigned int	color;
	int				tex_x;
	int				tex_y;
	int				d;

	d = y * 256 - sc->set.proj.hg * 128 + spt->hg * 128;
	tex_y = abs(((d * sc->texs[sc->anim.frame].hg) / spt->hg) / 256);
	tex_x = (int)(256 * (x - (-spt->wd / 2 + spt->screen_x))
			* sc->texs[sc->anim.frame].wd / spt->wd) / 256;
	color = tex_get_color(&sc->texs[sc->anim.frame], tex_x, tex_y);
	if (color != 4278190080)
		pixel_put_buffer(sc, x, y, color);
}

void	spt_render(t_scene *sc, t_spt_render *spt)
{
	int				y;
	int				x;

	y = spt->draw_start_y;
	while (y < spt->draw_end_y)
	{
		x = spt->draw_start_x;
		while (x < spt->draw_end_x)
		{
			if (spt->tsfm_y > 0 && x > 0 && x < sc->set.proj.wd
					&& spt->tsfm_y < sc->spt.z_buffer[x])
				spt_put_pixel(sc, spt, x, y);
			x++;
		}
		y++;
	}
}

void	spt_draw(t_scene *sc)
{
	t_spt_render	spt;
	int				i;

	spt_get_dist(sc);
	spt_sort(&sc->spt);
	i = 0;
	while (i < sc->spt.nb)
	{
		spt_set_data(sc, &spt, i);
		spt_render(sc, &spt);
		i++;
	}
}
