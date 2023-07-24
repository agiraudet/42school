/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 09:51:04 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/22 11:42:39 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		setting_tex_init(t_scene *sc)
{
	sc->nb_tex = 5 + BONUS * (2 + NB_FRAME);
	sc->set.tex_path = ft_calloc(sc->nb_tex, sizeof(char*));
	if (!sc->set.tex_path)
	{
		free(sc->map.str);
		error_set(MALLOC_ERROR, "tex_path array");
		return (0);
	}
	return (1);
}

int		setting_init(t_scene *sc, char *path, int prnt_scr)
{
	if (prnt_scr == 2)
	{
		sc->set.prnt_scr = 1;
		sc->view.win = 0;
	}
	else
		sc->set.prnt_scr = 0;
	sc->map.str = ft_strdup("");
	if (!sc->map.str)
	{
		error_set(MALLOC_ERROR, "function ft_strdup");
		return (0);
	}
	if (!setting_tex_init(sc))
		return (0);
	sc->map.size_x = 0;
	sc->map.size_y = 0;
	sc->map.size_tile = 64;
	if (!parse_file(sc, path))
	{
		free(sc->map.str);
		return (0);
	}
	return (1);
}

void	setting_res_set(t_settings *sets, const char *line)
{
	char	**values;
	int		i;

	values = ft_split(line, ' ');
	sets->win_x = ft_atoi(values[1]);
	sets->win_y = ft_atoi(values[2]);
	i = 0;
	while (values[i])
		free(values[i++]);
	free(values);
}

void	setting_tex_set(char **tex, const char *line)
{
	char	**values;
	int		i;

	values = ft_split(line, ' ');
	if (values[1][0] != 0)
		*tex = values[1];
	else
		*tex = 0;
	i = 0;
	while (values[i])
	{
		if (i != 1)
			free(values[i]);
		i++;
	}
	free(values);
}

void	setting_color_set(unsigned int *color, const char *line)
{
	char	**values;
	int		i;

	values = ft_split(line, ' ');
	*color = rgb_to_i(255, atoi(values[1]), atoi(values[2]), atoi(values[3]));
	i = 0;
	while (values[i])
		free(values[i++]);
	free(values);
}
