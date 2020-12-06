/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_map_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void		append_map_line(char *line, int i)
{
	int		j;
	char	s;

	if (line && *line)
	{
		j = 0;
		while (line[j])
		{
			s = (line[j] == ' ') ? '1' : line[j];
			s = (s == '0') ? '0' : s;
			s = (s == 'N') ? '0' : s;
			s = (s == 'W') ? '0' : s;
			s = (s == 'E') ? '0' : s;
			s = (s == 'S') ? '0' : s;
			game.field[i][j++] = s;
		}
		while (j < game.width)
			game.field[i][j++] = '1';
	}
}
