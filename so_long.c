/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nucieda- <nucieda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 23:14:19 by nucieda-          #+#    #+#             */
/*   Updated: 2023/03/10 05:01:51 by nucieda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_vars vars;
	t_data map;
	int	error;

	if (argc != 2)
		return (0);

	vars.mlx = mlx_init();
	vars.map = &map;
	
	error = load_map(&vars, argv[1]);
	if (error == 0)
	{
		printf("Load map failed\n");
		return (0);
	}
	
	mlx_key_hook(vars.win, keystroke, &vars);
	mlx_hook(vars.win, 17, 0, close_win, &vars);
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
	// W: 13
	// A: 0
	// S: 1
	// D: 2
	// Esc: 53

	if (keycode == 53)
		close_win(vars);
	update_map(vars, keycode);
	
	return (0);
}

int	close_win(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}