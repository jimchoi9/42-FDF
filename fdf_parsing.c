/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:21:49 by jimchoi           #+#    #+#             */
/*   Updated: 2024/04/09 20:46:26 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	str_check(t_data *image, char **str)
{
	int	check;
	int	length;

	length = 0;
	check = 0;
	image->width = 0;
	while (str[image->width] != NULL)
	{
		if (str[image->width][0] == '\n')
			check = 1;
		free(str[image->width]);
		if (length != image->width && length != 0)
			exit(1);
		image->width++;
	}
	if (check != 0)
		image->width -= 1;
}

int	is_valid_map(char *argv[], t_data *image)
{
	int		check;
	int		fd;
	char	*line;
	char	**str;

	check = 0;
	image->height = 0;
	image->width = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit (1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		str = ft_split(line, ' ');
		str_check(image, str);
		check = image->width;
		image->height++;
		free(line);
		free(str);
	}
	close(fd);
	return (open(argv[1], O_RDONLY));
}

void	init_struct(t_data *image)
{
	int	i;

	i = 0;
	if (image->width * image->height <= 1)
		exit(1);
	image->points = (t_point **)malloc(sizeof(t_point *) * image->height);
	image->map = (t_point **)malloc(sizeof(t_point *) * image->height);
	while (i < image->height)
	{
		image->points[i] = (t_point *)malloc(sizeof(t_point) * image->width);
		image->map[i] = (t_point *)malloc(sizeof(t_point) * image->width);
		i++;
	}
}

void	parsing(char *argv[], t_data *image, int i, int j)
{
	char	*line;
	char	**str;
	int		fd;

	fd = is_valid_map(argv, image);
	init_struct(image);
	while (++i < image->height)
	{
		line = get_next_line(fd);
		j = -1;
		str = ft_split(line, ' ');
		free(line);
		while (str[++j] != NULL)
		{
			if (str[j][0] != '\n')
			{
				image->points[i][j].x = j;
				image->points[i][j].y = i;
				image->points[i][j].z = ft_atoi(str[j]);
			}
			free(str[j]);
		}
		free(str);
	}
}
