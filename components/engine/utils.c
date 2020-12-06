/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int		ft_array_count(char **arr)
{
	int		i;

	i = 0;
	while (arr && *arr++)
		i++;
	return (i);
}

char	get_value_map(int y, int x)
{
	if (x >= 0 && x < game.width \
		&& y >= 0 && y < game.height)
	{
		return (game.field[y][x]);
	}
	return ('\0');
}

int		get_cell(double os)
{
	return ((int)(os / SQUARE_SIZE));
}

int		my_mlx_get_color(t_data *data, int x, int y)
{
	char	*dst;
	int		color;

	dst = data->addr + \
		(y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + \
		(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
