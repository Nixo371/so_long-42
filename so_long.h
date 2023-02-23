#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

#define WIN_LENGTH 800
#define WIN_HEIGHT 800

typedef struct s_square {
	int	centerx;
	int	centery;
	int	length;
	int	height;
}	t_square;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_square square;
}				t_vars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int		create_trgb(int t, int r, int g, int b);
int		add_shade(double distance, int color);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

void	draw_square(t_data data, int centerx, int centery, int length, int height);

int	keystroke(int keycode, t_vars *vars);

#endif