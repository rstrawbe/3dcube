#ifndef CUB3D_H
# define CUB3D_H

# define ALLOWED_MAP_CHARS " 012NSEW"
# define ALLOWED_DIRECTIONS "NSEW"


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
    int         floor_color;
    int         cell_color;
    int         textures_ready;
    int         window_width;
    int         window_height;
    int         width;
    int         height;
    char        vector_start;
    char        **field;
}               t_map;
#endif
