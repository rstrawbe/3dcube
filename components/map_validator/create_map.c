/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int	create_map(const char *filename)
{
	int		str_len;
	int		error;

	game.strnum = 0;
	game.map_file = (char *)filename;
	if ((error = read_line(&str_len)))
		return (error);
	if (!(ch_map((int)(hero.pos_x / SQUARE_SIZE), \
		(int)(hero.pos_y / SQUARE_SIZE))))
	{
		return (exit_with_error("Map is not valid", 1));
	}
	init_game();
	return (0);
}
