/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:20:53 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/09 20:52:43 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	abs(int num)
{
	if (num < 0)
		return (-num);
	else
		return (num);
}

void	bhm_drow_w(t_xy xy, t_linedata line, t_data image)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < line.w)
	{
		xy.x1 += line.add_x;
		count += line.h;
		if (count >= line.w)
		{
			xy.y1 += line.add_y;
			count -= line.w;
		}
		if (xy.x1 < WIDTH && xy.y1 < HEIGHT && xy.x1 >= 0 && xy.y1 >= 0)
			my_mlx_pixel_put(&image, xy.x1, xy.y1, WHITE);
		i++;
	}
}

void	bhm_drow_h(t_xy xy, t_linedata line, t_data image)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < line.h)
	{
		xy.y1 += line.add_y;
		count += line.w;
		if (count >= line.h)
		{
			xy.x1 += line.add_x;
			count -= line.h;
		}
		if (xy.x1 < WIDTH && xy.y1 < HEIGHT && xy.x1 >= 0 && xy.y1 >= 0)
			my_mlx_pixel_put(&image, xy.x1, xy.y1, WHITE);
		i++;
	}
}

void	bresenham(t_xy xy, int x2, int y2, t_data *image)
{
	t_linedata	line;

	line.add_x = 1;
	line.add_y = 1;
	line.w = abs(x2 - xy.x1);
	line.h = abs(y2 - xy.y1);
	if (x2 - xy.x1 < 0)
		line.add_x = -1;
	if (y2 - xy.y1 < 0)
		line.add_y = -1;
	if (line.w >= line.h)
		bhm_drow_w(xy, line, *image);
	else
		bhm_drow_h(xy, line, *image);
}
