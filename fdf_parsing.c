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

int	str_check(t_data *image, char **str)
{
	int	i;

	i = 0;
	image->width = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] != '\n')
			image->width++;
		free(str[i]);
		i++;
	}
	return (image->width);
}

int	is_valid_map(char *argv[], t_data *image)
{
	int		check;
	int		fd;
	char	*line;
	char	**str;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit (1);
	image->height = 0;
	line = get_next_line(fd);
	str = ft_split(line, ' ');
	check = str_check2(image, str);
	while (line != NULL)
	{
		str = ft_split(line, ' ');
		if (str_check2(image, str) != check)
			exit (1);
		image->height++;
		free(line);
		free(str);
		line = get_next_line(fd);
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
