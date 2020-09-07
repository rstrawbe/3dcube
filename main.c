#include <stdio.h>
#include "minilibx/mlx.h"
#include "cube3d.h"
#include "libft/libft.h"

#include "get_next_line/get_next_line.h"

//static int is_allowed_char(char ch)
//{
//    char    *allowed_str;
//
//    allowed_str = &ALLOWED_MAP_CHARS[0];
//    while (*allowed_str)
//        if (*allowed_str++ == ch)
//            return (1);
//    return (0);
//}

//static int validate_first_line(char *line)
//{
//
//}

static int validate_first_line(char *line)
{
    while (*line)
        if (*line++ != '1' || *line != '\t')
            return (0);
    return (1);
}

static int create_map(const char *filename)
{

    int fd;
    char	*line;
    int     i;
    char    *line_clean;

    i = 0;
    line = NULL;
    line_clean = NULL;

    if ((fd = open(filename, O_RDONLY)) == -1)
    {
        perror("open failed on input file");
        return (0);
    }
    while(get_next_line(fd, &line) >= 1)
    {
        if (!(line_clean = ft_strtrim(line, "\t")))
        {
            perror("err create line");
            return (1);
        }

        printf("%s\n", line_clean);

        if (++i == 1 && !validate_first_line(line_clean)) {
            perror("Map is not valid");
            return (1);
        }

        free(line);
        free(line_clean);
    }
    if (i <= 2) {
        perror("lines is <= 2");
        return (0);
    }

    if (!validate_first_line(line_clean))
    {
        perror("Map is not valid");
        return (0);
    }


    printf("%s\n", line_clean);
    free(line);
    //free(line_clean);

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
        perror("Error create_map");
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
