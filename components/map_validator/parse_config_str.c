/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static int	set_color(t_color *color, char **arr)
{
	char	**rgb;
	int		arr_count;

	rgb = ft_split(arr[1], ',');
	arr_count = ft_array_count(rgb);
	if (arr_count != 3)
		exit_with_error("Incorrect color", 100);
	color->color = create_rgb(ft_atoi(rgb[0]), \
	ft_atoi(rgb[1]), \
	ft_atoi(rgb[2]));
	color->is_init = 1;
	return (1);
}

static int	set_win_params(char **arr)
{
	int		screen_w;
	int		screen_h;

	mlx_get_screen_size(vars.mlx, &screen_w, &screen_h);
	game.window_width = ft_atoi(&arr[1][0]);
	game.window_height = ft_atoi(&arr[2][0]);
	if (game.window_width <= 300 \
		|| game.window_width > screen_w)
		game.window_width = screen_w;
	if (game.window_height <= 300
		|| game.window_height > screen_h)
		game.window_height = screen_h;
	return (1);
}

static int	set_path(char **dst, char *path)
{
	int		fd;
	char	**arr;
	int		arr_count;

	arr = ft_split(path, '.');
	arr_count = ft_array_count(arr);
	if (ft_strncmp(arr[arr_count - 1], "xpm", 4))
		return (0);
	if ((fd = open(path, O_RDONLY)) <= 0)
		return (0);
	close(fd);
	*dst = path;
	return (1);
}

int			parse_config_str(char *line)
{
	char	**arr;
	int		arr_count;

	arr = ft_split(line, ' ');
	if ((arr_count = ft_array_count(arr)) < 2)
		return (0);
	if (!ft_strncmp("R", &arr[0][0], EXT_LENGTH) && arr_count == 3)
		return (set_win_params(arr));
	if (!ft_strncmp("NO", &arr[0][0], EXT_LENGTH) && arr_count == 2)
		return (set_path(&game.north_texture, &arr[1][0]));
	if (!ft_strncmp("SO", &arr[0][0], EXT_LENGTH) && arr_count == 2)
		return (set_path(&game.south_texture, &arr[1][0]));
	if (!ft_strncmp("WE", &arr[0][0], EXT_LENGTH) && arr_count == 2)
		return (set_path(&game.west_texture, &arr[1][0]));
	if (!ft_strncmp("EA", &arr[0][0], EXT_LENGTH) && arr_count == 2)
		return (set_path(&game.east_texture, &arr[1][0]));
	if (!ft_strncmp("S", &arr[0][0], EXT_LENGTH) && arr_count == 2)
		return (set_path(&game.sprite_path, &arr[1][0]));
	if (!ft_strncmp("F", &arr[0][0], EXT_LENGTH) && arr_count == 2)
		return (set_color(&game.floor_color, arr));
	if (!ft_strncmp("C", &arr[0][0], EXT_LENGTH) && arr_count == 2)
		return (set_color(&game.cell_color, arr));
	return (0);
}
