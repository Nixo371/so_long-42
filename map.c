/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nucieda- <nucieda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:27:42 by nucieda-          #+#    #+#             */
/*   Updated: 2023/03/10 07:30:23 by nucieda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_map(t_vars *vars, char *map_file)
{
	int		i;
	int		j;
	int		map_length;
	int		map_height;
	int		tile_size;
	
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

	vars->win = mlx_new_window(vars->mlx, i, j, "Gamer Moment");

	vars->map->img = mlx_new_image(vars->mlx, i, j);
	vars->map->addr = mlx_get_data_addr(vars->map->img, &vars->map->bits_per_pixel, &vars->map->line_length, &vars->map->endian);
	vars->map->map = map_init(map_file, map_length, map_height);
	
	render_map(vars, map_length, map_height);

	return (1);
}

int	render_map(t_vars *vars, int map_length, int map_height)
{
	int		i;
	int		j;
	int		k;
	int		offset_x;
	int		offset_y;
	int		tile_size;
	char	tile_type;
	char	*file_name;
	
	i = 0;
	j = 0;
	if (map_length > 16)
		tile_size = 32;
	else if (map_length > 8)
		tile_size = 64;
	else
		tile_size = 128;
	k = map_length * tile_size;
	offset_x = 0;
	offset_y = 0;
	while (i < map_height)
	{
		while (j < map_length)
		{
			tile_type = vars->map->map[i][j];
			
			file_name = pick_xpm_file(tile_size, get_type(tile_type));
			vars->map->img = mlx_xpm_file_to_image(vars->mlx, file_name, &k, &k);
			mlx_put_image_to_window(vars->mlx, vars->win, vars->map->img, offset_x, offset_y);
			offset_x += tile_size;
			j++;
		}
		offset_x = 0;
		offset_y += tile_size;
		j = 0;
		i++;
	}
	return (0);
}

void	print_map(char **map)
{
	char	**tmp;

	tmp = map;
	while (*tmp)
	{
		printf("%s\n", *tmp);
		tmp++;
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

char	**map_init(char *file, int length, int height)
{
	int		fd;
	int		i;
	int		j;
	char	tile;
	char	**map = malloc(height * sizeof(char *) + 1);

	fd = open(file, O_RDONLY);
	if (!fd || !map)
		return (NULL);
	i = 0;
	j = 0;
	while (i < height)
	{
		*(map + i) = malloc(length * sizeof(char) + 1);
		i++;
	}
	*(map + i) = NULL;
	i = 0;
	while (i < height)
	{
		while (j < length)
		{
			if (read(fd, &tile, 1) != 1)
			{
				printf("This shouldn't happen\n");
				break ;	
			}
			map[i][j] = tile;
			//printf("This is tile: \"%c\" | This is map[%d][%d]: \"%c\"\n", tile, i, j, map[i][j]);
			j++;
		}
		read(fd, &tile, 1);
		map[i][j] = '\0';
		j = 0;
		i++;
	}
	close(fd);
	print_map(map);
	return (map);
}

int	update_map(t_vars *vars, int code)
{
	int	x;
	int	y;
	int x_o;
	int	y_o;

	x = code - code;
	y = 0;
	x_o = 0;
	y_o = 0;
	if (code == 13)
		y_o = -1;
	else if (code == 0)
		x_o = -1;
	else if (code == 1)
		y_o = 1;
	else if (code == 2)
		x_o = 1;
		
	find_player(vars->map->map, &x, &y);
	if (get_tile_type(vars->map->map, x + x_o, y + y_o) != 1)
	{
		if (get_tile_type(vars->map->map, x + x_o, y + y_o) == 3)
		{
			if (all_collectibles(vars->map->map))
			{
				printf("Movimientos Reales: %d\n", ++vars->moves);
				printf("you win\n");
				close_win(vars);
			}
			return (1);
		}
		vars->map->map[y][x] = '0';
		vars->map->map[y + y_o][x + x_o] = 'P';
		x = 0;
		y = 0;
		while (vars->map->map[y++]);
		while (vars->map->map[0][x++]);
		render_map(vars, --x, --y);
		printf("Movimientos Reales: %d\n", ++vars->moves);
		//print_map(vars->map->map);
	}
	return (1);
}

void	find_player(char **map, int *x, int *y)
{
	while (map[*y])
	{
		while(map[*y][*x])
		{
			if (map[*y][*x] == 'P')
				return ;
			*x += 1;
		}
		*x = 0;
		*y += 1;
	}
}

int	get_tile_type(char **map, int x, int y)
{
	return (get_type(map[y][x]));
}

int	all_collectibles(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while(map[i][j])
		{
			if (map[i][j] == 'C')
				return (0);
			j += 1;
		}
		j = 0;
		i += 1;
	}
	return (1);
}