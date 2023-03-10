/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nucieda- <nucieda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:14:19 by nucieda-          #+#    #+#             */
/*   Updated: 2023/03/10 01:18:43 by nucieda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_vars vars;
	t_data map_background;
	int	error;

	if (argc != 1)
		return (0);
	if (!argv)
		return (1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1024, 1024, "Gamer Moment");

	map_background.img = mlx_new_image(vars.mlx, 1024, 1024);
	map_background.addr = mlx_get_data_addr(map_background.img, &map_background.bits_per_pixel, &map_background.line_length, &map_background.endian);
	
	error = load_map(&map_background, &vars, "map.bar");
	if (error == 0)
	{
		printf("Load map failed\n");
		return (0);
	}

	mlx_loop(vars.mlx);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	keystroke(int keycode, t_vars *vars)
{
	if (vars->mlx)
		printf("Keycode: %d\n", keycode);
	
	return (0);
}