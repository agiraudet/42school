/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:41:08 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 15:25:25 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_plan_set(t_scene *sc, double px, double py)
{
	sc->plr.plan_x = px;
	sc->plr.plan_y = py;
}

void	player_dir_set(t_scene *sc, double dx, double dy)
{
	sc->plr.dir_x = dx;
	sc->plr.dir_y = dy;
}

void	move_dir_set_ns(t_scene *sc, char pos)
{
	if (pos == 'N' || pos == 'S')
	{
		sc->dir.up = 1;
		sc->dir.down = -1;
		if (pos == 'N')
		{
			sc->dir.left = -1;
			sc->dir.right = 1;
		}
		else
		{
			sc->dir.left = 1;
			sc->dir.right = -1;
		}
	}
}

void	move_dir_set_we(t_scene *sc, char pos)
{
	if (pos == 'W' || pos == 'E')
	{
		sc->dir.up = 1;
		sc->dir.down = -1;
		if (pos == 'W')
		{
			sc->dir.left = 1;
			sc->dir.right = -1;
		}
		else
		{
			sc->dir.left = -1;
			sc->dir.right = 1;
		}
	}
}

void	player_dir_init(t_scene *sc, char pos)
{
	if (pos == 'E')
	{
		player_dir_set(sc, 1., 0.);
		player_plan_set(sc, 0., 0.66);
	}
	if (pos == 'W')
	{
		player_dir_set(sc, -1., 0.);
		player_plan_set(sc, 0., 0.66);
	}
	if (pos == 'S')
	{
		player_dir_set(sc, 0., 1.);
		player_plan_set(sc, 0.66, 0.);
	}
	if (pos == 'N')
	{
		player_dir_set(sc, 0., -1.);
		player_plan_set(sc, 0.66, 0.);
	}
}
