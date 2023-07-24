/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:33:50 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 15:29:34 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_init(t_scene *sc)
{
	int		x;
	int		y;
	char	pos;

	y = 0;
	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
		{
			pos = sc->map.str[y * sc->map.size_x + x];
			if (ft_strchr("NEWS", pos))
			{
				sc->plr.pos_x = x;
				sc->plr.pos_y = y;
				player_dir_init(sc, pos);
				move_dir_set_ns(sc, pos);
				move_dir_set_we(sc, pos);
			}
			x++;
		}
		y++;
	}
}

void	player_go(t_scene *sc, int dir)
{
	float	new_x;
	float	new_y;

	new_x = sc->plr.pos_x + sc->plr.dir_x * dir * PLR_SPEED;
	new_y = sc->plr.pos_y + sc->plr.dir_y * dir * PLR_SPEED;
	if (sc->map.str[(int)new_y * sc->map.size_x + (int)new_x] != '1')
	{
		sc->plr.pos_x = new_x;
		sc->plr.pos_y = new_y;
	}
}

void	player_rot(t_scene *sc, int dir)
{
	double old_dir;
	double old_plane_x;

	old_dir = sc->plr.dir_x;
	sc->plr.dir_x = sc->plr.dir_x * cos(dir * ROT_SPEED)
		- sc->plr.dir_y * sin(dir * ROT_SPEED);
	sc->plr.dir_y = old_dir * sin(dir * ROT_SPEED)
		+ sc->plr.dir_y * cos(dir * ROT_SPEED);
	old_plane_x = sc->plr.plan_x;
	sc->plr.plan_x = sc->plr.plan_x * cos(dir * ROT_SPEED)
		- sc->plr.plan_y * sin(dir * ROT_SPEED);
	sc->plr.plan_y = old_plane_x * sin(dir * ROT_SPEED)
		+ sc->plr.plan_y * cos(dir * ROT_SPEED);
}

void	player_straf(t_scene *sc, int dir)
{
	double	new_x;
	double	new_y;
	double	straf_ang_x;
	double	straf_ang_y;

	dir *= -1;
	straf_ang_x = sc->plr.dir_y;
	straf_ang_y = -sc->plr.dir_x;
	new_x = sc->plr.pos_x + straf_ang_x * dir * PLR_SPEED;
	new_y = sc->plr.pos_y + straf_ang_y * dir * PLR_SPEED;
	if (sc->map.str[(int)new_y * sc->map.size_x + (int)new_x] != '1')
	{
		sc->plr.pos_x = new_x;
		sc->plr.pos_y = new_y;
	}
}

int		player_move(t_scene *sc)
{
	if (sc->key.rotl)
		player_rot(sc, sc->dir.left);
	if (sc->key.rotr)
		player_rot(sc, sc->dir.right);
	if (sc->key.up)
		player_go(sc, sc->dir.up);
	if (sc->key.down)
		player_go(sc, sc->dir.down);
	if (sc->key.strafl)
		player_straf(sc, sc->dir.left);
	if (sc->key.strafr)
		player_straf(sc, sc->dir.right);
	redraw_view(sc);
	return (1);
}
