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

    system("clear");
    map_print(map.field);
    usleep(2500);

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
    char *ln;

    ln=line;
    return (1);
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
    while(get_next_line(fd, &line) > 0)
    {
        str_len = ft_strlen(line);
        if (str_len && !config_is_init())
        {
            if (!parse_config_str(line))
                return (exit_with_error(null, 1));

            if (line[0] == 'R') {
                data = ft_split(line, ' ');
                printf("%s \n", data[1]);
                map.window_width = ft_atoi(&data[1][0]);
                map.window_height = ft_atoi(&data[2][0]);

                break;
            }
            set_texture_path(line);
        } else if (str_len && ++map.height) {
            if (!(is_line_of_allowed_char(line))) {
                return (exit_with_error(ERR_FORBIDDEN_SYMBOL_IN_MAP, 1));
            }
            i = 0;
            while (line[i]) {
                if (ft_strchr(&ALLOWED_DIRECTIONS[0], line[i])) {
                    if (hero.direction)
                        return (exit_with_error(ERR_MULTIPLE_POSITION, 1));
                    hero.pos_x_start = i;
                    hero.pos_y_start = map.height - 1;
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

    printf("config_is_init: %d\n", config_is_init());
    map.window_width = 10;
    map.window_height = 10;

    map.north_texture = &ALLOWED_DIRECTIONS[0];
    map.east_texture = &ALLOWED_DIRECTIONS[0];
    map.south_texture = &ALLOWED_DIRECTIONS[0];
    map.west_texture = &ALLOWED_DIRECTIONS[0];

    map.sprite_path = &ALLOWED_DIRECTIONS[0];

    map.floor_color.is_init = 1;
    map.cell_color.is_init = 1;

    printf("config_is_init: %d\n", config_is_init());

    return(0);


    printf("map.win_width: %d \n", map.window_width);
    printf("map.height: %d\n", map.height);
    printf("map.width: %d\n", map.width);


    if (map.height <= 2) {
        printf("lines is <= 2");
        return (0);
    }
    if (!hero.direction)
        return (0);

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

    while (get_next_line(fd, &line) > 0)
    {
        if ((str_len = ft_strlen(line)))
            append_map_line(line, i++);
        free(line);
    }
    free(line);

    if (!(ch_map(hero.pos_x_start, hero.pos_y_start))) {
        printf("\nMap not Valid\n");
        exit(0);
    }

    printf("++\n");
    printf("map.height: %d\n", map.height);

    printf("map.height: %d\n", map.height);
    printf("map.width: %d\n", map.width);

    printf("hero.pos_x_start: %d\n", hero.pos_x_start);
    printf("hero.pos_y_start: %d\n", hero.pos_y_start);

    return (1);
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
