/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static int	append_to_array(void)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	line = NULL;
	if ((fd = open(game.map_file, O_RDONLY)) == -1)
		return (exit_with_error(ERR_OPEN_FILE, 1));
	while (get_next_line(fd, &line) > 0)
	{
		if (game.strnum-- < 0 && ft_strlen(line))
			append_map_line(line, i++);
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}

static int	nulled_line(void)
{
	int		i;

	i = 0;
	while (i <= game.height)
		game.field[i++][game.width - 1] = '\0';
	return (append_to_array());
}

static int	error_allocate(void)
{
	int		i;

	i = 0;
	while (i <= game.height)
	{
		if (!(game.field[i++] = (char *)malloc(sizeof(char) * game.width + 1)))
		{
			while (--i >= 0)
				free(game.field[i]);
			free(game.field);
			return (exit_with_error("Error allocate", 201));
		}
	}
	return (nulled_line());
}

int			error_config(void)
{
	if (game.height <= 2)
		return (exit_with_error(ERR_MAP_SIZE, 1));
	if (!hero.direction)
		return (exit_with_error(ERR_HERO_POSITION, 1));
	if (!(game.field = (char **)malloc(sizeof(char **) * game.height)))
		return (exit_with_error("Error alloc", 1));
	if (error_allocate())
		return (exit_with_error("Error alloc", 1));
	return (0);
}
