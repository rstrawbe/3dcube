/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static void	change_texture(void)
{
	if (ray.depth_v < ray.depth_h && ray.dir_x < 0)
	{
		ray.wall_img = &vars.texture_w;
		ray.offset *= -1;
	}
	if (ray.depth_v < ray.depth_h && ray.dir_x > 0)
		ray.wall_img = &vars.texture_e;
	if (ray.depth_v > ray.depth_h && ray.dir_y < 0)
		ray.wall_img = &vars.texture_n;
	if (ray.depth_v > ray.depth_h && ray.dir_y > 0)
	{
		ray.wall_img = &vars.texture_s;
		ray.offset *= -1;
	}
	ray.texture_scale = ray.wall_img->w / SQUARE_SIZE;
}

static void	verticals(void)
{
	int	blocks;

	ray.y = ray.sin_a >= 0 ? ray.ym + SQUARE_SIZE : ray.ym;
	ray.dir_y = ray.sin_a >= 0 ? 1 : -1;
	blocks = game.height;
	while (blocks)
	{
		ray.depth_h = (ray.y - ray.yo) / ray.sin_a;
		ray.xh = ray.xo + ray.depth_h * ray.cos_a;
		ray.x_map = ray.xh / SQUARE_SIZE * SQUARE_SIZE;
		ray.y_map = ray.y / SQUARE_SIZE * SQUARE_SIZE;
		if (get_value_map(get_cell(ray.y_map + ray.dir_y), \
						get_cell(ray.x_map)) == '1')
			break ;
		ray.y += ray.dir_y * SQUARE_SIZE;
		blocks--;
	}
	ray.depth = ray.depth_v < ray.depth_h ? ray.depth_v : ray.depth_h;
	ray.offset = ray.depth_v < ray.depth_h ? ray.yv : ray.xh;
	ray.offset = (int)ray.offset % SQUARE_SIZE;
}

static void	set_vars(void)
{
	ray.depth *= cos(hero.angle - ray.cur_angle);
	ray.depth = ray.depth == 0 ? 0.00001 : ray.depth;
	ray.proj_h = ray.pr_coef / ray.depth < game.window_height * 2 ? \
				ray.pr_coef / ray.depth : game.window_height * 2;
	ray.texture_h = ray.proj_h > game.window_height ? \
				(ray.proj_h - game.window_height) / 2 : 0;
	ray.v_coef = ray.wall_img->h / ray.proj_h;
	ray.y_start = (int)(ray.half_height - ray.proj_h / 2);
	ray.y_start = ray.y_start < 0 ? 0 : ray.y_start;
	ray.proj_h = ray.proj_h > game.window_height ? \
				game.window_height : ray.proj_h;
	ray.y_end = ray.y_start + ray.proj_h;
	if (ray.texture_h * ray.v_coef > ray.wall_img->h)
		ray.texture_h = 0;
}

static void	horizontls(void)
{
	int	blocks;

	ray.sin_a = sin(ray.cur_angle);
	ray.cos_a = cos(ray.cur_angle);
	ray.x = ray.cos_a >= 0 ? ray.xm + SQUARE_SIZE : ray.xm;
	ray.dir_x = ray.cos_a >= 0 ? 1 : -1;
	blocks = game.width;
	while (blocks)
	{
		ray.depth_v = (ray.x - ray.xo) / ray.cos_a;
		ray.yv = ray.yo + ray.depth_v * ray.sin_a;
		ray.x_map = ray.x / SQUARE_SIZE * SQUARE_SIZE;
		ray.y_map = ray.yv / SQUARE_SIZE * SQUARE_SIZE;
		if (get_value_map(get_cell(ray.y_map), \
				get_cell(ray.x_map + ray.dir_x)) == '1')
			break ;
		ray.x += ray.dir_x * SQUARE_SIZE;
		blocks--;
	}
	verticals();
	change_texture();
	set_vars();
}

int			raycast(void)
{
	ray.num_rays = 0;
	mlx_do_sync(vars.mlx);
	clear();
	movement();
	ray.cur_angle = hero.angle - HALF_FOV;
	ray.xo = hero.pos_x;
	ray.yo = hero.pos_y;
	ray.xm = (int)hero.pos_x / SQUARE_SIZE * SQUARE_SIZE;
	ray.ym = (int)hero.pos_y / SQUARE_SIZE * SQUARE_SIZE;
	while (ray.num_rays < game.window_width)
	{
		horizontls();
		while (ray.y_start < ray.y_end)
		{
			ray.color = my_mlx_get_color(ray.wall_img, \
				ray.offset * ray.texture_scale, ray.texture_h * ray.v_coef);
			my_mlx_pixel_put(&vars.ray, ray.num_rays, ray.y_start, ray.color);
			ray.texture_h++;
			ray.y_start++;
		}
		ray.cur_angle += ray.delta_angle;
		ray.num_rays++;
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.ray.img, 0, 0);
	return (0);
}
