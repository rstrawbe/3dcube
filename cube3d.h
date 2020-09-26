#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>

# define ALLOWED_MAP_CHARS " 012NSEW"
# define ALLOWED_DIRECTIONS "NSEW"
# define EXT_LENGTH 5

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
    int         textures_ready;
    int         window_width;
    int         window_height;
    int         width;
    int         height;
    char        vector_start;
    char        **field;

    t_color     floor_color;
    t_color     cell_color;
}               t_map;
#endif
