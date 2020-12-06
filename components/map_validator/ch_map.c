/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int	is_line_of_allowed_char(char *line)
{
	char	*allowed_str;

	allowed_str = &ALLOWED_MAP_CHARS[0];
	while (*line)
	{
		if (!(ft_strchr(allowed_str, *line++)))
			return (0);
	}
	return (1);
}

int	ch_map(int x, int y)
{
	char	s;
	if ((x == game.width || x == -1) || (y == game.height || y == -1)) {
        return (0);
    }
	s = game.field[y][x] == '0' ? ' ' : 0;
	if (s)
	{
		game.field[y][x] = s;
		if (!ch_map(x, y - 1))
			return (0);
		if (!ch_map(x - 1, y))
			return (0);
		if (!ch_map(x, y + 1))
			return (0);
		if (!ch_map(x + 1, y))
			return (0);
	}
	return (1);
}
