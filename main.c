/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nucieda- <nucieda-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 18:18:31 by nucieda-          #+#    #+#             */
/*   Updated: 2023/02/22 19:46:41 by nucieda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(void)
{
	t_vars	vars;
	t_square square;
	t_data	img;
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_LENGTH, WIN_HEIGHT, "Window");
	
	img.img = mlx_new_image(vars.mlx, WIN_LENGTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	draw_square(img, 750, 200, 150, 150);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	
	square.centerx = WIN_LENGTH / 2;
	square.centerx = WIN_HEIGHT / 2;
	square.length = 100;
	square.height = 100;

	vars.square = square;

	mlx_hook(vars.win, 2, 1L<<0, keystroke, &vars);

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
	t_data data;

	data.img = mlx_new_image(vars->mlx, WIN_LENGTH, WIN_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	if (keycode == 13)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->square.centery -= 50;
	}
	if (keycode == 0)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->square.centerx -= 50;
	}
	if (keycode == 1)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->square.centery += 50;
	}
	if (keycode == 2)
	{
		mlx_clear_window(vars->mlx, vars->win);
		vars->square.centerx += 50;
	}
	draw_square(data, vars->square.centerx, vars->square.centery, vars->square.length, vars->square.height);
	mlx_put_image_to_window(vars->mlx, vars->win, data.img, 0, 0);
	
	return (0);
}