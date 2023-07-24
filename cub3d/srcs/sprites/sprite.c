/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:41:51 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/17 19:26:54 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spt_init(t_scene *sc)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = 0;
	while (y < sc->map.size_y)
	{
		x = 0;
		while (x < sc->map.size_x)
		{
			if (sc->map.str[y * sc->map.size_x + x] == '2')
			{
				sc->spt.buf[i].x = x + 0.5;
				sc->spt.buf[i].y = y + 0.5;
				sc->spt.buf[i].dist = 0;
				sc->spt.buf[i].hit = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	spt_get_dist(t_scene *sc)
{
	int		i;

	i = 0;
	while (i < sc->spt.nb)
	{
		sc->spt.buf[i].dist = ((sc->plr.pos_x - sc->spt.buf[i].x)
				* (sc->plr.pos_x - sc->spt.buf[i].x)
				+ (sc->plr.pos_y - sc->spt.buf[i].y)
				* (sc->plr.pos_y - sc->spt.buf[i].y));
		i++;
	}
}

void	spt_swap(t_sptbuf *sp1, t_sptbuf *sp2)
{
	t_sptbuf tmp;

	tmp = *sp1;
	*sp1 = *sp2;
	*sp2 = tmp;
}

void	spt_sort(t_spt *spt)
{
	int		i;

	if (spt->nb <= 1)
		return ;
	i = 1;
	while (i < spt->nb)
	{
		if (spt->buf[i].dist > spt->buf[i - 1].dist)
		{
			spt_swap(&spt->buf[i], &spt->buf[i - 1]);
			i = 0;
		}
		i++;
	}
}

int		spt_exist(t_scene *sc, int x, int y)
{
	int i;

	i = 0;
	while (i < sc->spt.count)
	{
		if (sc->spt.buf[i].x == x && sc->spt.buf[i].y == y)
			return (1);
		i++;
	}
	return (0);
}
