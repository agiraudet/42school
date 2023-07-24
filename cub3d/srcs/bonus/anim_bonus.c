/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:57:10 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 14:58:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				anim_init(t_scene *sc)
{
	sc->anim.frame = TEX_S;
	sc->anim.speed = 0;
	return (1);
}

void			anim_next_frame(t_scene *sc)
{
	if (sc->anim.speed >= ANIM_SPEED)
	{
		sc->anim.speed = 0;
		if (sc->anim.frame == TEX_S1)
			sc->anim.frame = TEX_S2;
		else
			sc->anim.frame = TEX_S1;
	}
	else
		sc->anim.speed += 1;
}
