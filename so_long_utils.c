/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nucieda- <nucieda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 08:32:46 by nucieda-          #+#    #+#             */
/*   Updated: 2023/03/10 08:41:56 by nucieda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_length(char **map)
{
	int	i;

	i = 0;
	while (map[i][0])
		i++;
	return (i);
}

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
		i++;
	return (i);
}

int	get_x(char **map, char tile)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == tile)
				return (i);
			j++;
		}
		j = 0;
		i++;
	}
	return (-1);
}

int	get_y(char **map, char tile)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == tile)
				return (j);
			j++;
		}
		j = 0;
		i++;
	}
	return (-1);
}