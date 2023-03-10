/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nucieda- <nucieda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:27:42 by nucieda-          #+#    #+#             */
/*   Updated: 2023/03/10 03:53:02 by nucieda-         ###   ########.fr       */
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
	int	map_height;
	int	tile_size;
	char	tile_type;
	char	*file_name;
	
	fd = open(map_file, O_RDONLY);
	
	i = 0;
	j = 0;
	map_length = 0;
	tile_size = 1;
	
	map_length = is_square(map_file, 0);
	map_height = is_square(map_file, 1);
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

	i = map_length * tile_size;
	j = map_height * tile_size;
	offset_x = 0;
	offset_y = 0;

	vars->win = mlx_new_window(vars->mlx, i, j, "Gamer Moment");

	map->img = mlx_new_image(vars->mlx, i, j);
	map->addr = mlx_get_data_addr(map->img, &map->bits_per_pixel, &map->line_length, &map->endian);
	
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
		file_name = pick_xpm_file(tile_size, j);
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
	char	*xpm_file = malloc(22 * sizeof(char));
	
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
			xpm_file = "./assets/032/walls.xpm";
		else if (tile_size == 64)
			xpm_file = "./assets/064/walls.xpm";
		else
			xpm_file = "./assets/128/walls.xpm";
	}
	else if (tile_type == 2)
	{
		if (tile_size == 32)
			xpm_file = "./assets/032/coins.xpm";
		else if (tile_size == 64)
			xpm_file = "./assets/064/coins.xpm";
		else
			xpm_file = "./assets/128/coins.xpm";
	}
	else if (tile_type == 3)
	{
		if (tile_size == 32)
			xpm_file = "./assets/032/exits.xpm";
		else if (tile_size == 64)
			xpm_file = "./assets/064/exits.xpm";
		else
			xpm_file = "./assets/128/exits.xpm";
	}
	else if (tile_type == 4)
	{
		if (tile_size == 32)
			xpm_file = "./assets/032/plays.xpm";
		else if (tile_size == 64)
			xpm_file = "./assets/064/plays.xpm";
		else
			xpm_file = "./assets/128/plays.xpm";
	}
	else
		return ("./assets/128/floor.xpm");
	return (xpm_file);
}

int	is_square(char *file_name, int sel)
{
	int		fd;
	int		count;
	int		length;
	int		height;
	char	tile;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("File failed to open\n");
		return (-1);
	}
	
	count = 0;
	length = 0;
	height = 1;
	while (read(fd, &tile, 1) == 1)
	{
		if (tile == '\n')
		{
			if (length != count && length != 0)
			{
				printf("Board is not square\n");
				return (-1);
			}
			length = count;
			height++;
			count = 0;
		}
		else
			count++;
	}
	if (tile != '1')
	{
		printf("Error\n");
		return (-1);
	}
	if (sel == 0)
		return (length);
	return (height);
	
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