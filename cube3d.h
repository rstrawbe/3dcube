/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <math.h>
# include <stdio.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

# include <errno.h>

# define ALLOWED_MAP_CHARS " 012NSEW"
# define ALLOWED_DIRECTIONS "NSEW"
# define EXT_LENGTH 5

# define STDERR 2
# define MAX_MAP_WIDTH 100
# define MAX_MAP_HEIGHT 100
# define ERR_ARG "Invalid argument"
# define ERR_MAP_EXT "Incorrect format: Use file with extension \".cub\""
# define ERR_OPEN_FILE "Failed to open file"
# define ERR_FORBIDDEN_SYMBOL_IN_MAP "Forbidden symbol found in the map"
# define ERR_HERO_POSITION "Player position not defined"
# define ERR_MAP_SIZE "Map size is wrong"
# define ERR_PARSE_CONFIG_LINE "Incorrect config line"

# define CODE_KEY_ESC 53
# define CODE_KEY_W 13
# define CODE_KEY_A 0
# define CODE_KEY_S 1
# define CODE_KEY_D 2
# define CODE_KEY_LEFT 123
# define CODE_KEY_RIGHT 124

# define SQUARE_SIZE 75

# define HERO_SPEED 10
# define HERO_ROT_SPEED 0.05
# define HERO_BODY SQUARE_SIZE * 0.8
# define FOV M_PI/3
# define HALF_FOV FOV/2

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			w;
	int			h;
}				t_data;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_data		minimap;
	t_data		ray;
	t_data		texture_w;
	t_data		texture_n;
	t_data		texture_s;
	t_data		texture_e;
	t_data		sprite;
}				t_vars;

typedef struct	s_btn {
	int			w;
	int			s;
	int			a;
	int			d;
	int			right;
	int			left;
}				t_btn;

typedef struct	s_color {
	int			is_init;
	int			red;
	int			green;
	int			blue;
	int			color;
}				t_color;

typedef struct	s_hero {
	double		angle;
	double		sin_a;
	double		cos_a;
	double		pos_x;
	double		pos_y;
	char		direction;
	int			speed;
	double		rot_speed;
}				t_hero;

typedef struct	s_game
{
	char		*map_file;
	int			strnum;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*sprite_path;
	int			window_width;
	int			window_height;
	int			width;
	int			height;
	char		**field;
	t_color		floor_color;
	t_color		cell_color;
	t_btn		btn_pressed;
	char		*error;
}				t_game;

typedef struct	s_ray
{
	double		cur_angle;
	double		delta_angle;
	double		xo;
	double		yo;
	double		xm;
	double		ym;
	double		x;
	double		y;
	double		xh;
	double		yv;
	double		proj_h;
	double		sin_a;
	double		cos_a;
	double		offset;
	double		texture_h;
	double		depth_v;
	double		depth_h;
	double		depth;
	double		pr_coef;
	double		v_coef;
	double		half_height;
	double		dist;
	int			dir_x;
	int			dir_y;
	double		x_map;
	double		y_map;
	double		texture_scale;
	int			color;
	int			y_start;
	int			y_end;
	int			num_rays;
	t_data		*wall_img;
}				t_ray;

struct s_game	game;
struct s_hero	hero;
struct s_vars	vars;
struct s_ray	ray;

int				create_rgb(int r, int g, int b);
int				get_cell(double os);
char			get_value_map(int y, int x);
int				init_map_validator();
void			movement();
int				raycast(void);
int				on_key_release(int keycode);
int				on_key_press_handler(int keycode);
void			init_game(void);
int				error_config(void);
int				read_line(int *str_len);
int				create_map(const char *filename);
void			render_minimap(t_vars *vars);
void			clear(void);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				my_mlx_get_color(t_data *data, int x, int y);
int				parse_config_str(char *line);
int				exit_with_error(char *str, int code);
int				check_file_ext(char *path, char *ext);
int				config_is_init(void);
int				ft_array_count(char **arr);
int				ch_map(int x, int y);
void			set_direction(char c);
void			append_map_line(char *line, int i);
int				is_line_of_allowed_char(char *line);
#endif
