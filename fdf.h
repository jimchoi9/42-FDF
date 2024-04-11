/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:18:23 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/09 20:49:13 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include "./minilibx_mms_20210621/mlx.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080
# define BLACK 0X111111
# define WHITE 0XFFFFFF

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
}		t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx_ptr;
	void	*win_ptr;

	int		width;
	int		height;
	int		z_level;
	t_point	**points;
	t_point	**map;
}		t_data;

typedef struct s_xy{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
}	t_xy;

typedef struct s_linedata{
	int	w;
	int	h;
	int	add_x;
	int	add_y;
}	t_linedata;

int		remove_window(t_data *image);
void	make_center(t_data *image, int w, int h);
void	convert_isometric(t_data *image);
void	draw_image(t_data *image);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	make_center(t_data *image, int w, int h);
void	convert_isometric(t_data *image);
void	draw_image(t_data *image);
int		abs(int num);
void	bhm_drow_w(t_xy xy, t_linedata line, t_data image);
void	bhm_drow_h(t_xy xy, t_linedata line, t_data image);
void	bhm(t_xy xy, int x2, int y2, t_data *image);
void	bresenham(t_xy xy, int x2, int y2, t_data *image);
void	str_check(t_data *image, char **str);
int		is_valid_map(char *argv[], t_data *image);
void	init_struct(t_data *image);
void	parsing(char *argv[], t_data *image, int i, int j);

#endif