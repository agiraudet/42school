/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 22:46:08 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 14:53:14 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_init_step(t_scene *sc, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (sc->plr.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - sc->plr.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (sc->plr.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - sc->plr.pos_y)
			* ray->delta_dist_y;
	}
}

void	ray_init(t_scene *sc, int x, t_ray *ray)
{
	double cam_x;

	cam_x = 2 * x / (double)sc->set.proj.wd - 1;
	ray->dir_x = sc->plr.dir_x + sc->plr.plan_x * cam_x;
	ray->dir_y = sc->plr.dir_y + sc->plr.plan_y * cam_x;
	ray->map_x = (int)sc->plr.pos_x;
	ray->map_y = (int)sc->plr.pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	ray_init_step(sc, ray);
}

double	ray_get_dist(t_scene *sc, t_ray *ray)
{
	if (ray->side == 0 || ray->side == 1)
		ray->perp_wall_dist = (ray->map_x - sc->plr.pos_x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - sc->plr.pos_y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_hg = (int)(sc->set.proj.hg / ray->perp_wall_dist);
	return (ray->perp_wall_dist);
}

void	dda(t_scene *sc, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			if (ray->step_x == -1)
				ray->side = 0;
			else
				ray->side = 1;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			if (ray->step_y == -1)
				ray->side = 2;
			else
				ray->side = 3;
		}
		if (sc->map.str[ray->map_y * sc->map.size_x + ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	raycast(t_scene *sc)
{
	t_ray	ray;
	int		x;

	if (BONUS)
		ground_render(sc);
	sc->spt.count = 0;
	x = 0;
	while (x < sc->set.proj.wd)
	{
		ray_init(sc, x, &ray);
		dda(sc, &ray);
		sc->spt.z_buffer[x] = ray_get_dist(sc, &ray);
		ray_draw(sc, &ray, x);
		x++;
	}
}
