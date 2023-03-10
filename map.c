/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nucieda- <nucieda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:27:42 by nucieda-          #+#    #+#             */
/*   Updated: 2023/03/10 01:35:05 by nucieda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_map(t_data *map, t_vars *vars, char *map_file)
{
	int fd;
	int	i;
	int	j;
	int	offset_x;
	int	offset_y;
	int	map_length;
	int	tile_size;
	char	tile_type;
	char	*file_name;
	
	fd = open(map_file, O_RDONLY);
	
	i = 0;
	j = 0;
	map_length = 0;
	tile_size = 1;
	
	map_length = is_square();
	if (map_length == -1)
		return (0);

	if (map_length > 16)
		tile_size = 32;
	else if (map_length > 8)
		tile_size = 64;
	else
		tile_size = 128;
	printf("Map Length: %d\n", map_length);
	printf("Tile Size: %d\n", tile_size);

	i = 128;
	offset_x = 0;
	offset_y = 0;
	while (offset_y < (tile_size * map_length))
	{
		j = read(fd, &tile_type, 1);
		if (j == 0)
			break;
		if (tile_type == '\n')
		{
			j = read(fd, &tile_type, 1);
			if (j == 0)
				break;
			offset_x = 0;
			offset_y += tile_size;
		}
		j = get_type(tile_type);
		file_name = pick_xpm_file(tile_size, 0);
		map->img = mlx_xpm_file_to_image(vars->mlx, file_name, &i, &i);
		mlx_put_image_to_window(vars->mlx, vars->win, map->img, 0 + offset_x, 0 + offset_y);
		offset_x += tile_size;
	}
	return (1);
}

void	print_map(char **map)
{
	int i;

	i = 0;

	printf("uh oh\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

char	*pick_xpm_file(int tile_size, int tile_type)
{
	
	char	*xpm_file = malloc(31 * sizeof(char));
	
	if (tile_type == 0)
	{
		if (tile_size == 32)
			xpm_file = "./assets/032/floor.xpm";
		else if (tile_size == 64)
			xpm_file = "./assets/064/floor.xpm";
		else
			xpm_file = "./assets/128/floor.xpm";
	}
	else if (tile_type == 1)
	{
		if (tile_size == 32)
			xpm_file = "./assets/032/floor.xpm";
		else if (tile_size == 64)
			xpm_file = "./assets/064/floor.xpm";
		else
			xpm_file = "./assets/128/floor.xpm";
	}
	return (xpm_file);
}

int	is_square()
{
	return (13);
}

int	get_type(char tile_type)
{
	if (tile_type == '0')
		return (0);
	else if (tile_type == '1')
		return (1);
	else if (tile_type == 'C')
		return (2);
	else if (tile_type == 'E')
		return (3);
	else if (tile_type == 'P')
		return (4);
	else
		return (-1);
}

/*
while (1)
	{
		map_line[i] = malloc(20 * sizeof(char));
		tile_size = read(fd, map_line[i], 1);
		if (tile_size != 1)
			break;
		j++;
		if (map_line[i][j] == '\n')
		{
			if (map_length != j && map_length != 0)
			{
				printf("Map not square\n");
				return (0);
			}
			map_length = j;
			j = 0;
			i++;
		}
	}
	printf("Here\n");
	print_map((char **)map_line);
*/