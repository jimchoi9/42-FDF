/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:37:22 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/09 20:52:29 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	remove_window(t_data *image)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(image, x, y, BLACK);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(image->mlx_ptr, image->win_ptr, image->img, 0, 0);
	return (0);
}

int	handle_key_hook(int keycode, t_data *image)
{
	remove_window(image);
	if (keycode == 126)
		image->z_level += 1;
	if (keycode == 125)
		image->z_level -= 1;
	convert_isometric(image);
	draw_image(image);
	mlx_put_image_to_window(image->mlx_ptr, image->win_ptr, image->img, 0, 0);
	return (0);
}

int	key_press_esc(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int	exit_key(void)
{
	exit(0);
}

int	main(int argc, char *argv[])
{
	char	*str;
	t_data	image;

	if (argc != 2)
		exit(1);
	str = ft_strrchr(argv[1], '.');
	if (ft_strncmp(str, ".fdf", 3) != 0)
		exit(1);
	parsing(argv, &image, -1, -1);
	image.mlx_ptr = mlx_init();
	image.win_ptr = mlx_new_window(image.mlx_ptr, WIDTH, HEIGHT, "fdf");
	image.img = mlx_new_image(image.mlx_ptr, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, \
		&image.line_length, &image.endian);
	image.z_level = 4;
	convert_isometric(&image);
	draw_image(&image);
	mlx_put_image_to_window(image.mlx_ptr, image.win_ptr, image.img, 0, 0);
	mlx_hook(image.win_ptr, 2, 0, &key_press_esc, &image);
	mlx_hook(image.win_ptr, 17, 0, &exit_key, 0);
	mlx_key_hook(image.win_ptr, handle_key_hook, &image);
	mlx_loop(image.mlx_ptr);
	exit (0);
}


// void check_leaks(void) 
// { system("leaks fdf"); } 
// atexit(check_leaks);