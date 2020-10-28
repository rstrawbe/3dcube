#include <math.h>
#include <stdio.h>
#include "minilibx/mlx.h"


typedef struct s_data
{
  void     *img;
  char    *addr;
  int      bits_per_pixel;
  int      line_length;
  int      endian;
}        t_data;


void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char  *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned char *)dst = color;
}

int      main(void)
{
  void  *mlx;
  t_data  img;
  t_data bg_img;
  void  *mlx_win;

  mlx = mlx_init();
  mlx_win = mlx_new_window(mlx, 800, 600, "Hello World!");
  img.img = mlx_new_image(mlx, 70, 50);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
                &img.line_length, &img.endian);

  bg_img.img = mlx_new_image(mlx, 700, 500);
  bg_img.addr = mlx_get_data_addr(bg_img.img, &bg_img.bits_per_pixel,
                &bg_img.line_length, &bg_img.endian);

  int bg_color = 0xfffaf0;

  int color = 0x00FF0000;

  int i = 0, j = 0;
  while (i < 600){
      j=0;
      while (j < 400) {
          my_mlx_pixel_put(&bg_img, i, j, bg_color);
          j++;
      }
      i++;
  }

  mlx_put_image_to_window(mlx, mlx_win, bg_img.img, 10, 10);
  mlx_loop(mlx);

  /*=========================================
  ** Для того чтобы выровнять байты относительно нашего окна(ЭТО НАДО ДЕЛАТЬ ВСЕГДА!)
  ** надо взять следующую формулу:
  ** int offset = (y * line_length + x * (bits_per_pixel / 8));
  *//*===========================================*/
}