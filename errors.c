/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nucieda- <nucieda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:07:46 by nucieda-          #+#    #+#             */
/*   Updated: 2023/03/10 08:37:50 by nucieda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	repeat_chars(char **map)
{
	int	i;
	int	j;
	int	found_p;
	int	found_e;

	i = 0;
	j = 0;
	found_p = 0;
	found_e = 0;

	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				if (found_p)
					return (1);
				found_p = 1;
			}
			else if (map[i][j] == 'E')
			{
				if (found_e)
					return (1);
				found_e = 1;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	surrounded(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 0;
	max = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1')
			return (0);
		i++;
	}
	i--;
	while (map[j][i])
	{
		if (map[j][i] != '1')
			return (0);
		j++;
	}
	j--;
	while (i >= 0)
	{
		if (map[j][i] != '1')
			return (0);
		i--;
	}
	while (j >= 0)
	{
		if (map[j][0] != '1')
			return (0);
		j--;
	}
	return (1);
}

int	possible_path(char **map)
{
	int	length;
	int	height;
	int	*possible[2];

	length = get_length(map);
	height = get_height(map);
	possible[0] = malloc(((length - 2) * (height - 2)) * sizeof(int));
	possible[1] = malloc(((length - 2) * (height - 2)) * sizeof(int));

	
}