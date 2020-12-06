/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_is_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int	config_is_init(void)
{
	return (game.window_height && game.window_width \
			&& game.north_texture && game.south_texture \
			&& game.west_texture && game.east_texture && game.sprite_path \
			&& game.floor_color.is_init && game.cell_color.is_init);
}
