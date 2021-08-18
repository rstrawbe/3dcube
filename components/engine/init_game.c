/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static void	init_buttons(void)
{
	game.btn_pressed.left = 0;
	game.btn_pressed.right = 0;
	game.btn_pressed.w = 0;
	game.btn_pressed.a = 0;
	game.btn_pressed.s = 0;
	game.btn_pressed.d = 0;
}

static void	set_image(t_data *pt, char *path)
{
	pt->img = mlx_xpm_file_to_image(vars.mlx, path, &pt->w, &pt->h);
	pt->addr = mlx_get_data_addr(pt->img, \
					&pt->bits_per_pixel, \
					&pt->line_length, \
					&pt->endian);
}

static void	set_images(void)
{
	set_image(&vars.texture_w, game.west_texture);
	set_image(&vars.texture_n, game.north_texture);
	set_image(&vars.texture_s, game.south_texture);
	set_image(&vars.texture_e, game.east_texture);
	set_image(&vars.sprite, game.sprite_path);
}

static void	create_ray_img(void)
{
	vars.ray.img = mlx_new_image(vars.mlx,
			game.window_width, game.window_height);
	vars.ray.addr = mlx_get_data_addr(vars.ray.img, \
					&vars.ray.bits_per_pixel, \
					&vars.ray.line_length, \
					&vars.ray.endian);
}

static	void	create_minimap(void)
{
	vars.minimap.img = mlx_new_image(vars.mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	vars.minimap.addr = mlx_get_data_addr(vars.minimap.img, \
					&vars.minimap.bits_per_pixel, \
					&vars.minimap.line_length, \
					&vars.minimap.endian);
}

void		init_game(void)
{
	vars.win = mlx_new_window(vars.mlx, game.window_width, \
						game.window_height, GAME_TITLE);
	ray.delta_angle = FOV / game.window_width;
	ray.dist = game.window_width / (2 * tan(HALF_FOV));
	ray.pr_coef = ray.dist * SQUARE_SIZE;
	ray.half_height = game.window_height / 2;
	create_ray_img();
	create_minimap();
	set_images();
	init_buttons();
	mlx_hook(vars.win, 2, 1L << 0, on_key_press_handler, NULL);
	mlx_hook(vars.win, 3, 1L << 1, on_key_release, NULL);
	mlx_loop_hook(vars.mlx, raycast, &vars);
	mlx_loop(vars.mlx);
}
