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

static void ft_array_clean(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}


static int create_map(const char *filename)
{
    int     i;
    int     fd;
    char	*line;
    int     str_len;
    char    **data;

    map.width = 0;
    map.height = 0;

    if ((fd = open(filename, O_RDONLY)) == -1)
        return (0);

    i = 0;

    int arrcnt = 0;
    line = NULL;
    data = NULL;
    //map.textures_ready = 1;
    while(get_next_line(fd, &line) > 0)
    {
        str_len = ft_strlen(line);
        if (str_len && !map.textures_ready)
        {

            if (line[0] == 'R') {
                data = ft_split(line, ' ');

                arrcnt = ft_array_count(data);
                printf("%s \n", data[1]);
                map.window_width = ft_atoi(&data[1][0]);
                map.window_height = ft_atoi(&data[2][0]);
                printf("window_width %d \n", map.window_width);
                printf("window_height %d \n", map.window_height);

                //ft_array_clean(data);

                break;
            }
            set_texture_path(line);
        }

        if (str_len && map.textures_ready && ++map.height) {
            if (!(is_line_of_allowed_char(line))) {
                printf("no valid!\n");
                return (0);
            }

            i = 0;
            while (line[i]) {
                if (ft_strchr(&ALLOWED_DIRECTIONS[0], line[i])) {
                    if (hero.direction)
                        return (0);
                    hero.pos_x_start = i;
                    hero.pos_y_start = map.height - 1;
                    set_direction(&hero, line[i]);
                }
                i++;
            }
            map.width = str_len > map.width ? str_len : map.width;
            if (map.width > 100 || map.height > 100) {
                printf("Error\nLong map");
                return (0);
            }
        }
        free(line);
    }
    free(line);
    close(fd);

    printf("arrcnt: %d \n", arrcnt);
    printf("map.win_width: %d \n", map.window_width);
    printf("map.height: %d\n", map.height);
    printf("map.width: %d\n", map.width);


    exit(0);

    ft_array_clean(data);

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

    return (1);


}


int             main(int argc, char **argv)
{
//    void    *mlx;
//    void    *mlx_win;

    if (argc < 2) {
        perror("Error. You must add path/to/map.cub as second argument!");
        return (1);
    }


    if (!create_map( argv[1])) {
        printf("Error create_map");
    }

//    printf("S isAllowed: %d\n", is_allowed_char('S'));
//    printf("1 isAllowed: %d\n", is_allowed_char('1'));
//    printf("2 isAllowed: %d\n", is_allowed_char('2'));
//    printf("Q isAllowed: %d\n", is_allowed_char('Q'));
//
//    printf("S ft_strchr: %p\n", ft_strchr(ALLOWED_MAP_CHARS, 'S'));
//    printf("1 ft_strchr: %p\n", ft_strchr(ALLOWED_MAP_CHARS, '1'));
//    printf("2 ft_strchr: %p\n", ft_strchr(ALLOWED_MAP_CHARS, '2'));
//    printf("Q ft_strchr: %p\n", ft_strchr(ALLOWED_MAP_CHARS, 'Q'));
//
//    if (ft_strchr(ALLOWED_MAP_CHARS, 'S'))
//        printf("S in str\n");
//
//    if (ft_strchr(ALLOWED_MAP_CHARS, '4'))
//        printf("4 in str\n");
//    else
//        printf("4 not in str\n");
    return (1);


//    mlx = mlx_init();
//    mlx_win = mlx_new_window(mlx, 800, 400, "старт!");
//
//	mlx_pixel_put(mlx, mlx_win, 5,5, 0x00FFF000);
//    mlx_loop(mlx);
}
