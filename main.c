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

static int validate_first_line(char *line)
{

}

static void create_map(const char *filename)
{

    int fd;
    char	*line;
    int     i;

    i = 0;
    line = NULL;
    fd = open(filename, O_RDONLY);

    while(get_next_line(fd, &line) == 1)
    {
        if (++i == 1)
            validate_first_line(line);
        printf("%s\n", line);
        free(line);
    }
    if (i <= 2)
        printf("lines is <= 2");

    validate_first_line(line);

    printf("%s\n", line);
    free(line);


}


int             main(void)
{
//    void    *mlx;
//    void    *mlx_win;

    create_map("map.cub");

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
