/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:38:19 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/21 20:44:55 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_bonus(t_scene *sc, const char *line)
{
	if (cmp_id(line, "SA"))
		setting_tex_set(&sc->set.tex_path[TEX_S1], line);
	else if (cmp_id(line, "SB"))
		setting_tex_set(&sc->set.tex_path[TEX_S2], line);
	else if (cmp_id(line, "TF"))
		setting_tex_set(&sc->set.tex_path[TEX_F], line);
	else if (cmp_id(line, "BG"))
		setting_tex_set(&sc->set.tex_path[TEX_BG], line);
}
