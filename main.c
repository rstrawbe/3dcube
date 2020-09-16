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

static  char **map_copy()
{
    int i;
    int j;
    char **copy_map;

    i = 0;
    j = 0;

    if (!(copy_map = (char **)malloc(sizeof(char **) * map.height + 1)))
        return (NULL);

    while (i < map.height) {
        if (!(copy_map[i++] = (char *) malloc(sizeof(char) * map.width + 1)))
        {
            while (--i >= 0)
                free(copy_map[i]);
            free(copy_map);
            return (NULL);
        }
    }
    *copy_map[i - 1] = '\0';

    i = 0;
    j = 0;

    while (copy_map[i])
        copy_map[i++][map.width] = '\0';
    i = 0;
    while (i < map.height)
    {
        while (j < map.width)
        {
            copy_map[i][j] = map.field[i][j];
            j++;
        }
        i++;
        j = 0;
    }
    return (copy_map);
}

static void append_map_line(char *line, int i)
{
    int j;
    char s;

    j = 0;
    while (line[j])
    {
        s = (line[j] == ' ') ? '1' : line[j];
        map.field[i][j++] = s;

    }
    while (j < map.width)
        map.field[i][j++] = '1';
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

static char next_val(t_hero *h, char **arr)
{
    if (h->direction == 'N')
    {
        if (h->pos_y - 1 < 0)
            return ('e');
        return (arr[h->pos_y - 1][h->pos_x]);
    } else if (h->direction == 'W')
    {
        if (h->pos_x - 1 < 0)
            return ('e');
        return (arr[h->pos_y][h->pos_x - 1]);
    } else if (h->direction == 'S')
    {
        if (h->pos_y + 1 >= map.height)
            return ('e');
        return (arr[h->pos_y + 1][h->pos_x]);
    } else if (h->direction == 'E')
    {
        if (h->pos_x + 1 >= map.width)
            return ('e');
        return (arr[h->pos_y][h->pos_x + 1]);
    }
    return ('e');
}

static char right_val(t_hero *h, char **arr)
{
    if (h->direction == 'N')
        return (arr[h->pos_y][h->pos_x + 1]);
    else if (h->direction == 'W')
        return (arr[h->pos_y - 1][h->pos_x]);
    else if (h->direction == 'S')
        return (arr[h->pos_y][h->pos_x - 1]);
    else if (h->direction == 'E')
        return (arr[h->pos_y + 1][h->pos_x]);
    return ('e');
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

static void step_forward(t_hero *h)
{
    h->pos_x += h->vector_x;
    h->pos_y += h->vector_y;
}


static int create_map(const char *filename)
{
    int i;
    int j;
    int     fd;
    char	*line;
    int     str_len;
    char    **copy_map;
    t_hero  copy_hero;
    int     check_process;

    line = NULL;

    map.width = 0;
    map.height = 0;

    i = 0;
    j = 0;

    if ((fd = open(filename, O_RDONLY)) == -1)
        return (0);
    while(get_next_line(fd, &line) >= 0 && (str_len = ft_strlen(line)) && ++map.height)
    {
        if (!(is_line_of_allowed_char(line))) {
            printf("no valid!\n");
            return (0);
        }

        i = 0;
        while (line[i])
        {
            if (line[i] == 'N')
            {
                if (hero.pos_x_start)
                    return (0);
                hero.pos_x_start = i;
                hero.pos_y_start = map.height - 1;
                set_direction(&hero, line[i]);
            }

            if (line[i] == 'W')
            {
                if (hero.pos_x_start)
                    return (0);

                hero.pos_x_start = i;
                hero.pos_y_start = map.height - 1;
                set_direction(&hero, line[i]);
            }

            if (line[i] == 'S')
            {
                if (hero.pos_x_start)
                    return (0);

                hero.pos_x_start = i;
                hero.pos_y_start = map.height - 1;
                set_direction(&hero, line[i]);
            }

            if (line[i] == 'E')
            {
                if (hero.pos_x_start)
                    return (0);

                hero.pos_x_start = i;
                hero.pos_y_start = map.height - 1;
                set_direction(&hero, line[i]);
            }
            i++;
        }

        map.width = str_len > map.width ? str_len : map.width;
        free(line);
    }

    if (map.height <= 2) {
        printf("lines is <= 2");
        return (0);
    }
    free(line);

    close(fd);
    if ((fd = open(filename, O_RDONLY)) == -1)
        return (0);

    map.field = (char **)malloc(sizeof(char **) * map.height + 1);

    i = 0;
    j = 0;

    while (i < map.height)
        map.field[i++] = (char *)malloc(sizeof(char) * map.width + 1);

    *map.field[i - 1] = '\0';

    i = 0;
    j = 0;

    while (map.field[i])
        map.field[i++][map.width] = '\0';

    i = 0;
    j = 0;
    while (get_next_line(fd, &line) >= 1)
    {
        append_map_line(line, i++);
        free(line);
    }
    append_map_line(line, i++);
    free(line);


//    printf("pos_x_start: %d\n", hero.pos_x_start);
//    printf("pos_y_start: %d\n", hero.pos_y_start);
//    printf("vector_x: %d\n", hero.vector_x);
//    printf("vector_y: %d\n\n\n", hero.vector_y);

    if (!(copy_map = map_copy()))
        return (0);


    copy_hero.vector_x = hero.vector_x;
    copy_hero.vector_y = hero.vector_y;

    copy_hero.pos_x_start = hero.pos_x_start;
    copy_hero.pos_y_start = hero.pos_y_start;

    copy_hero.pos_x = hero.pos_x_start;
    copy_hero.pos_y = hero.pos_y_start;

    copy_hero.direction = hero.direction;

    check_process = 1;

    char s;
    int cnt = 0;
    while (cnt < 4)
    {
        copy_hero.pos_y = hero.pos_y_start;
        copy_hero.pos_x = hero.pos_x_start;
        set_direction(&copy_hero, ALLOWED_DIRECTIONS[cnt++]);

        while (next_val(&copy_hero, copy_map) == '0'
        || next_val(&copy_hero, copy_map) == ' ') {
            step_forward(&copy_hero);
        }
        copy_hero.pos_y_start = copy_hero.pos_y;
        copy_hero.pos_x_start = copy_hero.pos_x;
        turn_left(&copy_hero);

        while (next_val(&copy_hero, copy_map) != 'e') {

            s = ' ';
            copy_map[copy_hero.pos_y][copy_hero.pos_x] = s;

            system("clear");
            map_print(copy_map);

            printf("\n\npos_x_start: %d\n", copy_hero.pos_x_start);
            printf("pos_y_start: %d\n", copy_hero.pos_y_start);

            printf("pos_x: %d\n", copy_hero.pos_x);
            printf("pos_y: %d\n", copy_hero.pos_y);
            printf("direction: %c\n", copy_hero.direction);
            printf("vector_x: %d\n", copy_hero.vector_x);
            printf("vector_y: %d\n", copy_hero.vector_y);

            printf("nval: %c\n", next_val(&copy_hero, copy_map));
            printf("rval: %c\n", right_val(&copy_hero, copy_map));

            usleep(100000);

            if (next_val(&copy_hero, copy_map) == '1'
            && right_val(&copy_hero, copy_map) != '0'
            && right_val(&copy_hero, copy_map) != ' ') {
                turn_left(&copy_hero);
            } else if ((right_val(&copy_hero, copy_map) == '0'
                || right_val(&copy_hero, copy_map) == ' ')
                ) {
                turn_right(&copy_hero);
            }

            if (next_val(&copy_hero, copy_map) != '1') {
                step_forward(&copy_hero);

                if (((copy_hero.pos_y_start == copy_hero.pos_y)
                    && (copy_hero.pos_x_start == copy_hero.pos_x)))
                    break;
            }

        }

        system("clear");
        map_print(copy_map);

        printf("\n\npos_x: %d\n", copy_hero.pos_x);
        printf("pos_y: %d\n", copy_hero.pos_y);
        printf("direction: %c\n", copy_hero.direction);
        printf("vector_x: %d\n", copy_hero.vector_x);
        printf("vector_y: %d\n", copy_hero.vector_y);

        if (next_val(&copy_hero, copy_map) == 'e')
        {
            printf("Error\n Map is not Valid\n");
            check_process = 0;
            break;
        }

        if ((copy_hero.pos_y_start == copy_hero.pos_y)
            && (copy_hero.pos_x_start == copy_hero.pos_x) && cnt == 3)
        {
            printf("Map is Valid\n");
            check_process = 0;
            //break;
        }
    }


    exit(0);

    turn_right(&copy_hero);

    exit(0);

//    Справа стена {
//      i = 0
//        Пока Впереди стена {
//            if (++i == 4)
//              {return valid}
//            Поворот налево
//        }
//        Шаг Вперед
//    } else {
//        Поворот направо
//        Шаг вперед
//
//    }


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
