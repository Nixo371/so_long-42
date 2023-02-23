#include "so_long.h"

void	draw_square(t_data data, int centerx, int centery, int length, int height)
{
	int	x;
	int	y;
	int	color;

	x = centerx - (length / 2);
	y = centery - (height / 2);
	color = create_trgb(0, 255, 0, 0);

	while (y < (centery + (height / 2)))
	{
		while (x < (centerx + (length / 2)))
		{
			if (x > 0 && x < WIN_LENGTH && y > 0 && y < WIN_HEIGHT)
				my_mlx_pixel_put(&data, x, y, color);
			x++;
		}
		x = centerx - (length / 2);
		y++;
	}

}