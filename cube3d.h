#ifndef CUB3D_H
# define CUB3D_H

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

# define SQUARE_SIZE 32

# define FOV 1.0471975512
# define HALF_FOV HFOV/2
# define NUM_RAYS 120
# define MAX_DEPTH 800
# define DELTA_ANGLE FOV/NUM_RAYS
# define DIST NUM_RAYS/ 1.15470053836
# define PROJECT_COEFF DIST * SQUARE_SIZE


typedef struct s_btn {
    int     w;
    int     s;
    int     a;
    int     d;

    int     right;
    int     left;
}               t_btn;

typedef struct s_color {
    int     is_init;
    int     red;
    int     green;
    int     blue;
}               t_color;

typedef struct s_hero {
    int     pos_x_start;
    int     pos_y_start;

    double angle;

    int     pos_x;
    int     pos_y;

    char    direction;
    int     vector_x;
    int     vector_y;
    float   planeY;
    float   planeX;

    float   dirX;
    float   dirY;

    int posX;
    int posY;
}               t_hero;

typedef struct  s_map
{
    char        *north_texture;
    char        *south_texture;
    char        *west_texture;
    char        *east_texture;
    char        *sprite_path;
    int         window_width;
    int         window_height;
    int         width;
    int         height;
    char        vector_start;
    char        **field;

    int         full_w;
    int         full_h;

    t_color     floor_color;
    t_color     cell_color;

    t_btn       btn_pressed;

    char        *error;
}               t_map;
#endif
