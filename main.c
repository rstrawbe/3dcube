#include "minilibx/mlx.h"



int             main(void)
{
    void    *mlx;
    void    *mlx_win;


    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 800, 400, "старт!");


	mlx_pixel_put(mlx, mlx_win, 5,5, 0x00FFF000);
    mlx_loop(mlx);
}
