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
# define ERR_MULTIPLE_POSITION "Multiple player positions on the map"
# define ERR_MAP_SIZE "The size of the map is too large"

typedef struct s_color {
    int     is_init;
    int     red;
    int     green;
    int     blue;
}               t_color;

typedef struct s_hero {
    int     pos_x_start;
    int     pos_y_start;

    int     pos_x;
    int     pos_y;

    char    direction;
    int     vector_x;
    int     vector_y;
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

    t_color     floor_color;
    t_color     cell_color;

    char        *error;
}               t_map;
#endif
