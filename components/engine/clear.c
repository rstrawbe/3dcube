/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static void	line(int y, int color)
{
	int	j;

	j = 0;
	while (j < game.window_width)
		my_mlx_pixel_put(&vars.ray, j++, y, color);
}

void		clear(void)
{
	int	color;
	int	i;

	i = 0;
	while (i < game.window_height)
	{
		color = i < game.window_height / 2 ? \
				game.cell_color.color : game.floor_color.color;
		line(i, color);
		i++;
	}
}
