/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 15:07:37 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/22 11:33:16 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spt_destroy(t_scene *sc)
{
	free(sc->spt.z_buffer);
	free(sc->spt.buf);
	free(sc->map.str);
}

void	settings_destroy(t_scene *sc)
{
	int		i;

	i = 0;
	while (i < sc->nb_tex)
		free(sc->set.tex_path[i++]);
	free(sc->set.tex_path);
}

void	textures_destroy(t_scene *sc)
{
	int		i;

	i = 0;
	while (i < sc->set.nb_tex_loaded)
		mlx_destroy_image(sc->view.mlx, sc->texs[i++].ptr);
}

int		scene_destroy(t_scene *sc)
{
	t_view	view;

	textures_destroy(sc);
	settings_destroy(sc);
	free(sc->texs);
	mlx_destroy_image(sc->view.mlx, sc->img_buf.ptr);
	spt_destroy(sc);
	view = sc->view;
	if (sc->view.win_alive)
		mlx_destroy_window(sc->view.mlx, sc->view.win);
	free(sc);
	exit(error_exit());
}
