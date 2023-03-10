#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

int		keystroke(int keycode, t_vars *vars);

void	print_map(char **map);
int		is_square(char *file_name, int sel);
int		get_type(char tile_type);

int		load_map(t_data *map, t_vars *vars, char *map_file);
char	*pick_xpm_file(int tile_size, int tile_type);

#endif