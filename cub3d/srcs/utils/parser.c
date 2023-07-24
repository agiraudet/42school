/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:46:08 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/22 12:42:01 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		cmp_id(const char *str, const char *id)
{
	if (*str == *id && *(str + 1) == *(id + 1))
		return (1);
	return (0);
}

void	parse_line(t_scene *sc, const char *line)
{
	if (cmp_id(line, "R "))
		setting_res_set(&sc->set, line);
	else if (cmp_id(line, "NO"))
		setting_tex_set(&sc->set.tex_path[TEX_NO], line);
	else if (cmp_id(line, "SO"))
		setting_tex_set(&sc->set.tex_path[TEX_SO], line);
	else if (cmp_id(line, "WE"))
		setting_tex_set(&sc->set.tex_path[TEX_WE], line);
	else if (cmp_id(line, "EA"))
		setting_tex_set(&sc->set.tex_path[TEX_EA], line);
	else if (cmp_id(line, "S "))
		setting_tex_set(&sc->set.tex_path[TEX_S], line);
	else if (cmp_id(line, "F "))
		setting_color_set(&sc->set.color_f, line);
	else if (cmp_id(line, "C "))
		setting_color_set(&sc->set.color_c, line);
	else if (ft_strchr(" 1", *line) && *line)
		map_add(&sc->map, line);
}

int		parse_file(t_scene *sc, char *path)
{
	int		fd;
	char	*line;

	if (!check_extension(path))
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_set(PATH_ERROR, path);
		return (0);
	}
	while (get_next_line(fd, &line) > 0)
	{
		parse_line(sc, line);
		if (BONUS)
			parse_bonus(sc, line);
		free(line);
	}
	free(line);
	if (check_map(sc) == 0)
		return (0);
	return (1);
}
