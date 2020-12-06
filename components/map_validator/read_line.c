/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static int	read_map_line(char *line, int *str_len)
{
	int		i;

	i = 0;
	if (!(is_line_of_allowed_char(line)))
		return (exit_with_error(ERR_FORBIDDEN_SYMBOL_IN_MAP, 1));
	while (line[i])
	{
		if (ft_strchr(&ALLOWED_DIRECTIONS[0], line[i]))
		{
			if (hero.direction)
				return (exit_with_error(ERR_HERO_POSITION, 1));
			hero.pos_x = i * SQUARE_SIZE + SQUARE_SIZE / 2;
			hero.pos_y = (game.height - 1) * SQUARE_SIZE + SQUARE_SIZE / 2;
			set_direction(line[i]);
		}
		i++;
	}
	game.width = *str_len > game.width ? *str_len : game.width;
	if (game.width > MAX_MAP_WIDTH || game.height > MAX_MAP_HEIGHT)
		return (exit_with_error(ERR_MAP_SIZE, 1));
	return (0);
}

int			read_line(int *str_len)
{
	char	*line;
	int		error;
	int		fd;

	line = NULL;
	if ((fd = open(game.map_file, O_RDONLY)) == -1)
		return (exit_with_error(ERR_OPEN_FILE, 1));
	while (get_next_line(fd, &line) == 1)
	{
		if (!config_is_init())
			game.strnum++;
		if ((*str_len = ft_strlen(line)) && !config_is_init())
		{
			if (!parse_config_str(line))
				return (exit_with_error(ERR_PARSE_CONFIG_LINE, 1));
		}
		else if (*str_len && config_is_init() && ++game.height)
		{
			if ((error = read_map_line(line, str_len)))
				return (error);
		}
		free(line);
	}
	free(line);
	return (error_config());
}
