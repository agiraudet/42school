/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:09:56 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/16 17:39:56 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bmp_file_header(int fd, t_tex *img)
{
	int	file_size;
	int	start_address;

	start_address = 14 + 40 + 4;
	file_size = start_address + (img->wd * img->hg) * 2;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &start_address, 4);
}

void	bmp_image_header(int fd, t_tex *img)
{
	int		header_size;
	int		bi_planes;
	int		i;

	header_size = 40;
	bi_planes = 1;
	write(fd, &header_size, 4);
	write(fd, &img->wd, 4);
	write(fd, &img->hg, 4);
	write(fd, &bi_planes, 2);
	write(fd, &img->bpp, 2);
	i = 0;
	while (i < 24)
	{
		write(fd, "\0", 1);
		i++;
	}
}

void	bmp_pixel_data(int fd, t_tex *img)
{
	int		x;
	int		y;

	y = img->hg - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < img->wd)
		{
			write(fd, &img->data[y * img->line_len + (img->bpp / 8) * x], 4);
			x++;
		}
		y--;
	}
}

int		bmp_to_file(t_tex *img, char *path)
{
	int		fd;

	fd = open(path, O_CREAT | O_RDWR, 0666);
	if (fd == -1)
	{
		perror("error");
	}
	bmp_file_header(fd, img);
	bmp_image_header(fd, img);
	bmp_pixel_data(fd, img);
	close(fd);
	return (1);
}
