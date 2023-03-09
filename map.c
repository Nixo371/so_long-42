/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nucieda- <nucieda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:27:42 by nucieda-          #+#    #+#             */
/*   Updated: 2023/03/10 00:05:16 by nucieda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_map(t_data *map, t_vars *vars, char *map_file)
{
	//int fd;
	int	i;
	int	j;
	int	map_length;
	//char	**map_line;
	
	//fd = open(map_file, O_RDONLY);
	
	i = 0;
	j = 0;
	map_length = 0;
	if (!map_file)
		return (0);
	/*
	while (read(fd, map_line[i], 1) == 1)
	{
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
	*/
	map->img = mlx_xpm_file_to_image(vars->mlx, "./assets/floor/floor_1.xpm", &i, &j);
	return (1);
}

void	print_map(char **map)
{
	int i;

	i = 0;

	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}