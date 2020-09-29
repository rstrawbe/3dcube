#include <stdio.h>
#include "minilibx/mlx.h"
#include "cube3d.h"
#include "libft/libft.h"

#include "get_next_line/get_next_line.h"

static t_map map;

static t_hero hero;

static int is_line_of_allowed_char(char *line)
{
    char    *allowed_str;

    allowed_str = &ALLOWED_MAP_CHARS[0];
    while (*line) {
        if (!(ft_strchr(allowed_str, *line++)))
            return (0);
    }
    return (1);
}

static  void map_print(char **arr)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < map.height)
    {
        while (j < map.width)
            ft_putchar_fd(arr[i][j++], 1);
        ft_putchar_fd('\n', 1);
        i++;
        j = 0;
    }
}

static void append_map_line(char *line, int i)
{
    int j;
    char s;

    if (line && *line) {
        j = 0;
        while (line[j]) {
            s = (line[j] == ' ') ? '1' : line[j];
            map.field[i][j++] = s;

        }
        while (j < map.width)
            map.field[i][j++] = '1';
    }
}

static void step_forward(t_hero *h)
{
    int new_x;
    int new_y;

    new_x = h->pos_x + h->vector_x;
    new_y = h->pos_y + h->vector_y;
    if (map.field[new_y][new_x] == ' ') {
        map.field[h->pos_y][h->pos_x] = ' ';
        h->pos_x = new_x;
        h->pos_y = new_y;
        map.field[new_y][new_x] = hero.direction;
    }
}


static void turn_right(t_hero *h)
{
    if (h->direction == 'N')
    {
        h->vector_x = 1;
        h->vector_y = 0;
        h->direction = 'E';
    } else if (h->direction == 'W')
    {
        h->vector_x = 0;
        h->vector_y = -1;
        h->direction = 'N';
    } else if (h->direction == 'S')
    {
        h->vector_x = -1;
        h->vector_y = 0;
        h->direction = 'W';
    } else if (h->direction == 'E')
    {
        h->vector_x = 0;
        h->vector_y = 1;
        h->direction = 'S';
    }

}

static void turn_left(t_hero *h)
{
    if (h->direction == 'N')
    {
        h->vector_x = -1;
        h->vector_y = 0;
        h->direction = 'W';
    } else if (h->direction == 'W')
    {
        h->vector_x = 0;
        h->vector_y = 1;
        h->direction = 'S';
    } else if (h->direction == 'S')
    {
        h->vector_x = 1;
        h->vector_y = 0;
        h->direction = 'E';
    } else if (h->direction == 'E')
    {
        h->vector_x = 0;
        h->vector_y = -1;
        h->direction = 'N';
    }

}


static void set_direction(t_hero *h, char c)
{
    if (c == 'N')
    {
        h->vector_x = 0;
        h->vector_y = -1;
    }
    if (c == 'W')
    {
        h->vector_x = -1;
        h->vector_y = 0;
    }
    if (c == 'S')
    {
        h->vector_x = 0;
        h->vector_y = 1;
    }
    if (c == 'E')
    {
        h->vector_x = 1;
        h->vector_y = 0;
    }
    h->direction = c;
}

static int ch_map(int x, int y)
{
    char s;

    if ((x == map.width || x == -1) || (y == map.height || y == -1))
        return (0);
    s = map.field[y][x] == '0' ? ' ' : 0;
    s = !s && map.field[y][x] == 'N' ? 'N' : s;
    s = !s && map.field[y][x] == 'S' ? 'S' : s;
    s = !s && map.field[y][x] == 'W' ? 'W' : s;
    s = !s && map.field[y][x] == 'E' ? 'E' : s;
    if (s) {
        map.field[y][x] = s;
        if (!ch_map(x, y - 1))
            return (0);
        if (!ch_map(x - 1, y ))
            return (0);
        if (!ch_map(x, y + 1))
            return (0);
        if (!ch_map(x + 1, y))
            return (0);
    }
    return (1);
}

int set_texture_path(char *line)
{
    if (line && line[0] && line[1])
        return (1);
    return (0);
}

static int ft_array_count(char **arr)
{
    int i;

    i = 0;
    while (arr && *arr++)
        i++;
    return (i);
}

static int	config_is_init(void)
{
    return (map.window_height && map.window_width
            && map.north_texture && map.south_texture
            && map.west_texture && map.east_texture && map.sprite_path
            && map.floor_color.is_init && map.cell_color.is_init);
}

static int check_file_ext(char *path, char *ext)
{
    char **path_parts;
    int parts_count;

    if (!(path_parts = ft_split(path, '.')))
        return (0);
    parts_count = ft_array_count(path_parts);
    if (ft_strncmp(path_parts[parts_count - 1], ext, EXT_LENGTH))
        return 0;
    if (parts_count == 1)
        return (0);
    return (1);
}


static int exit_with_error(char *str, int code)
{
    ft_putstr_fd("Error\n", STDERR);
    ft_putstr_fd(str, STDERR);
    ft_putstr_fd("\n", STDERR);
    return (code);
}

int parse_config_str(char *line)
{
    char **arr;
    int arr_count;

    arr = ft_split(line, ' ');
    arr_count = ft_array_count(arr);
    if (arr_count < 2) {
        printf("str: %s\n", arr[0]);
        return (0);
    }
    if (!ft_strncmp("R", &arr[0][0], EXT_LENGTH) && arr_count == 3)
    {
        map.window_width = ft_atoi(&arr[1][0]);
        map.window_height = ft_atoi(&arr[2][0]);
        return (1);
    }
    if (!ft_strncmp("NO", &arr[0][0], EXT_LENGTH) && arr_count == 2)
        if ((map.north_texture = ft_strdup(&arr[1][0])))
            return (1);
    if (!ft_strncmp("SO", &arr[0][0], EXT_LENGTH) && arr_count == 2)
        if ((map.south_texture = ft_strdup(&arr[1][0])))
            return (1);
    if (!ft_strncmp("WE", &arr[0][0], EXT_LENGTH) && arr_count == 2)
        if ((map.west_texture = ft_strdup(&arr[1][0])))
            return (1);
    if (!ft_strncmp("EA", &arr[0][0], EXT_LENGTH) && arr_count == 2)
        if ((map.east_texture = ft_strdup(&arr[1][0])))
            return (1);
    if (!ft_strncmp("S", &arr[0][0], EXT_LENGTH) && arr_count == 2)
        if ((map.sprite_path = ft_strdup(&arr[1][0])))
            return (1);

    if (!ft_strncmp("F", &arr[0][0], EXT_LENGTH) && arr_count == 2)
        if ((map.floor_color.is_init = 1))
            return (1);
    if (!ft_strncmp("C", &arr[0][0], EXT_LENGTH) && arr_count == 2)
        if ((map.cell_color.is_init = 1))
            return (1);

    return (0);
}

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_vars {
    void        *mlx;
    void        *win;

    t_data      minimap;
}               t_vars;


void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void render_minimap(t_vars *vars)
{

    int x = 0;
    int y = 0;

    int c1 = 0x3ea135;
    int c0 = 0xffffff;
    int c3 = 0x630505;
    int c_def = 0x000FBF21;

    int ofsX = -19;
    int ofsY = -9;
    int startX;
    int startY;

    int i = 0;
    int j = 0;


    while (ofsY < 10)
    {
        j = 0;
        ofsX = -19;
        while (ofsX < 20)
        {
            startY = hero.pos_y + ofsY;
            startX = hero.pos_x + ofsX;

            if ((startY > map.height - 1)
                || (startY < 0)
                || (startX > map.width - 1)
                || (startX < 0)) {
                c_def = 0x858585;
            } else {
                c_def = map.field[startY][startX] == '1' ? c1 : c_def;
                c_def = map.field[startY][startX] == ' ' ? c0 : c_def;
                c_def = map.field[startY][startX] == 'S' ? c3 : c_def;
                c_def = map.field[startY][startX] == 'N' ? c3 : c_def;
                c_def = map.field[startY][startX] == 'W' ? c3 : c_def;
                c_def = map.field[startY][startX] == 'E' ? c3 : c_def;
            }

            y = 0;
            while (y < 5) {
                x = 0;
                while (x < 5) {
                    my_mlx_pixel_put(&vars->minimap, j*5 + x, i*5 + y, c_def);
                    x++;
                }
                y++;
            }
            j++;
            ofsX++;
        }
        i++;
        ofsY++;
    }

    if (vars) {}

    mlx_put_image_to_window(vars->mlx, vars->win, vars->minimap.img, 0, 0);
}

int             on_key_press_handler(int keycode, t_vars *vars)
{
    if (keycode == CODE_KEY_UP) {
        step_forward(&hero);
    }
    if (keycode == CODE_KEY_RIGHT) {
        turn_right(&hero);
    }
    if (keycode == CODE_KEY_LEFT) {
        turn_left(&hero);
    }
    render_minimap(vars);
    if (keycode == CODE_KEY_ESC) {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    return (0);
}


static void map_render(void)
{
    void    *mlx;
    void    *mlx_win;

    t_vars      vars;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, map.window_width, map.window_height, "старт!");

    vars.mlx = mlx;
    vars.win = mlx_win;

    vars.minimap.img = mlx_new_image(mlx, 200, 100);
    vars.minimap.addr = mlx_get_data_addr(vars.minimap.img,
                                          &vars.minimap.bits_per_pixel,
                                          &vars.minimap.line_length,
                                          &vars.minimap.endian);

    render_minimap(&vars);
    mlx_key_hook(vars.win, on_key_press_handler, &vars);


    mlx_loop(mlx);
}

static int create_map(const char *filename)
{
    int     i;
    int     fd;
    char	*line;
    int     str_len;
    char    **data;

    line = NULL;
    data = NULL;
    map.width = 0;
    map.height = 0;

    if ((fd = open(filename, O_RDONLY)) == -1)
        return (exit_with_error(ERR_OPEN_FILE, 1));

    i = 0;
    int strnum = 0;
    while(get_next_line(fd, &line) > 0)
    {
        if (!config_is_init())
            ++strnum;
        str_len = ft_strlen(line);
        if (str_len && !config_is_init())
        {
            if (!parse_config_str(line))
                return (exit_with_error(ERR_PARSE_CONFIG_LINE, 1));
        } else if (str_len && config_is_init() && ++map.height) {
            if (!(is_line_of_allowed_char(line)))
                return (exit_with_error(ERR_FORBIDDEN_SYMBOL_IN_MAP, 1));
            i = 0;
            while (line[i]) {
                if (ft_strchr(&ALLOWED_DIRECTIONS[0], line[i])) {
                    if (hero.direction)
                        return (exit_with_error(ERR_HERO_POSITION, 1));
                    hero.pos_x = i;
                    hero.pos_y = map.height - 1;
                    set_direction(&hero, line[i]);
                }
                i++;
            }
            map.width = str_len > map.width ? str_len : map.width;
            if (map.width > MAX_MAP_WIDTH || map.height > MAX_MAP_HEIGHT)
                return (exit_with_error(ERR_MAP_SIZE, 1));
        }
        free(line);
    }
    free(line);
    close(fd);

    if (map.height <= 2) {
        return (exit_with_error(ERR_MAP_SIZE, 1));
    }
    if (!hero.direction)
        return (exit_with_error(ERR_HERO_POSITION, 1));

    i = 0;
    if (!(map.field = (char **)malloc(sizeof(char **) * map.height)))
        return (0);
    while (i < map.height) {
        if (!(map.field[i++] = (char *)malloc(sizeof(char) * map.width + 1)))
        {
            while (--i >= 0)
                free(map.field[i]);
            free(map.field);

            printf("\nError allocate:\n");
            exit(0);
        }
    }
    map.field[i] = NULL;

    i = 0;
    while (map.field[i])
        map.field[i++][map.width] = '\0';

    i = 0;
    if ((fd = open(filename, O_RDONLY)) == -1)
        return (0);
    while (get_next_line(fd, &line) > 0 && strnum--)
        free(line);
    while (get_next_line(fd, &line) > 0)
    {
        if ((str_len = ft_strlen(line)))
            append_map_line(line, i++);
        free(line);
    }
    free(line);

    if (!(ch_map(hero.pos_x, hero.pos_y)))
        return (exit_with_error("Map is not valid", 1));

    map_print(map.field);

    map_render();

    return (0);
}

int             main(int argc, char **argv)
{
//    void    *mlx;
//    void    *mlx_win;

    if (argc < 2)
        return (exit_with_error(ERR_ARG, 1));

    if (!check_file_ext(argv[1], "cub"))
        return (exit_with_error(ERR_MAP_EXT, 1));

    return create_map(argv[1]);


//    mlx = mlx_init();
//    mlx_win = mlx_new_window(mlx, 800, 400, "старт!");
//
//	mlx_pixel_put(mlx, mlx_win, 5,5, 0x00FFF000);
//    mlx_loop(mlx);
}
