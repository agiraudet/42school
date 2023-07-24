/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:43:34 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/22 11:42:44 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		buffer_init(t_scene *sc)
{
	t_tex	*buffer;

	buffer = &sc->img_buf;
	buffer->wd = sc->set.win_x;
	buffer->hg = sc->set.win_y;
	buffer->ptr = mlx_new_image(sc->view.mlx, sc->set.win_x, sc->set.win_y);
	if (!buffer->ptr)
	{
		error_set(1, "pointer to image buffer");
		return (0);
	}
	buffer->data = mlx_get_data_addr(buffer->ptr, &buffer->bpp,
										&buffer->line_len, &buffer->endian);
	if (!buffer->data)
	{
		error_set(1, "data space of image buffer");
		free(buffer->ptr);
		return (0);
	}
	return (1);
}

int		view_init(t_scene *sc)
{
	int screen_x;
	int screen_y;

	sc->view.mlx = mlx_init();
	if (!sc->view.mlx)
		return (0);
	screen_x = 0;
	screen_y = 0;
	mlx_get_screen_size(sc->view.mlx, &screen_x, &screen_y);
	if (screen_x < sc->set.win_x)
		sc->set.win_x = screen_x;
	if (screen_y < sc->set.win_y)
		sc->set.win_y = screen_y;
	proj_set(sc);
	if (sc->set.prnt_scr)
	{
		sc->view.win_alive = 0;
		return (1);
	}
	sc->view.win = mlx_new_window(sc->view.mlx,
		sc->set.win_x, sc->set.win_y, "cub3d");
	if (!sc->view.win)
		return (0);
	sc->view.win_alive = 1;
	return (1);
}

int		spt_buffer_init(t_scene *sc)
{
	int		i;

	i = 0;
	sc->spt.nb = 0;
	while (sc->map.str[i])
		if (sc->map.str[i++] == '2')
			sc->spt.nb++;
	sc->spt.z_buffer = malloc(sizeof(double*) * sc->set.proj.wd);
	if (!sc->spt.z_buffer)
	{
		error_set(MALLOC_ERROR, "z_buffer");
		return (0);
	}
	sc->spt.buf = malloc(sizeof(t_sptbuf) * sc->spt.nb);
	if (!sc->spt.buf)
	{
		error_set(MALLOC_ERROR, "spt_buffer");
		free(sc->spt.buf);
		return (0);
	}
	spt_init(sc);
	return (1);
}

int		scene_init_2(t_scene *sc)
{
	player_init(sc);
	key_init(sc);
	if (sc->view.win_alive)
		hook_init(sc);
	if (!buffer_init(sc))
	{
		settings_destroy(sc);
		spt_destroy(sc);
		free(sc);
		return (0);
	}
	if (!tex_init(sc))
	{
		scene_destroy(sc);
		return (0);
	}
	if (BONUS)
		anim_init(sc);
	else
		sc->anim.frame = TEX_S;
	return (1);
}

t_scene	*scene_init_1(char *path, int prnt_scr)
{
	t_scene	*sc;

	sc = malloc(sizeof(t_scene));
	if (!sc)
	{
		error_set(MALLOC_ERROR, "scene object");
		return (0);
	}
	if (!setting_init(sc, path, prnt_scr))
	{
		free(sc);
		return (0);
	}
	view_init(sc);
	if (!spt_buffer_init(sc))
	{
		settings_destroy(sc);
		free(sc);
		return (0);
	}
	minimap_init(sc);
	if (!scene_init_2(sc))
		return (0);
	return (sc);
}
