/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:42:41 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/09 20:53:14 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	make_center(t_data *image, int w, int h)
{
	int	i;
	int	j;

	i = 0;
	w = WIDTH / 2 - image->map[image->height / 2][image->width / 2].x;
	h = HEIGHT / 2 - image->map[image->height / 2][image->width / 2].y \
	-image->points[image->height / 2][image->width / 2].z * image->z_level;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
		{
			image->map[i][j].x += w;
			image->map[i][j].y += h;
			j++;
		}
		i++;
	}
}

void	convert_isometric(t_data *image)
{
	int		i;
	int		j;
	t_xy	xy;
	double	theta;
	int		gap;

	theta = M_PI / 6;
	i = 0;
	gap = WIDTH / 3 / image->width;
	while (i < image->height)
	{
		j = -1;
		while (++j < image->width)
		{
				xy.x2 = image->points[i][j].x * gap;
				xy.y2 = image->points[i][j].y * gap ;
				xy.x1 = (xy.x2 - xy.y2) * cos(theta);
				xy.y1 = (xy.x2 + xy.y2) * sin(theta) \
					- image->points[i][j].z * image->z_level;
				image->map[i][j].x = xy.x1;
				image->map[i][j].y = xy.y1;
		}
		i++;
	}
}

void	draw_image(t_data *image)
{
	int		i;
	int		j;
	t_xy	xy;

	i = -1;
	xy.x2 = WIDTH / 2 - image->map[image->height / 2][image->width / 2].x;
	xy.y2 = HEIGHT / 2 - image->map[image->height / 2][image->width / 2].y ;
	make_center(image, xy.x2, xy.y2 - \
	image->map[image->height / 2][image->width / 2].z * image->z_level);
	while (++i < image->height)
	{
		j = -1;
		while (++j < image->width)
		{
			xy.x1 = image->map[i][j].x;
			xy.y1 = image->map[i][j].y ;
			if (j < image->width - 1)
				bresenham(xy, image->map[i][j + 1].x, \
					image->map[i][j + 1].y, image);
			if (i < image->height - 1)
				bresenham(xy, image->map[i + 1][j].x, \
					image->map[i + 1][j].y, image);
		}
	}
}
