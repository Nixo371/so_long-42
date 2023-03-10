#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**map;
}	t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		moves;
	t_data	*map;
}	t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

int		keystroke(int keycode, t_vars *vars);
int		close_win(t_vars *vars);

void	print_map(char **map);
int		is_square(char *file_name, int sel);
int		get_type(char tile_type);
int		get_tile_type(char **map, int x, int y);

int		all_collectibles(char **map);

char	**map_init(char *file, int length, int height);
int		load_map(t_vars *vars, char *map_file);
int		render_map(t_vars *vars, int map_length, int map_height);
int		update_map(t_vars *vars, int code);
void	find_player(char **map, int *x, int *y);

char	*pick_xpm_file(int tile_size, int tile_type);

#endif