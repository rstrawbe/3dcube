/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int			check_file_ext(char *path, char *ext)
{
	char	**path_parts;
	int		parts_count;

	if (!(path_parts = ft_split(path, '.')))
		return (0);
	parts_count = ft_array_count(path_parts);
	if (ft_strncmp(path_parts[parts_count - 1], ext, EXT_LENGTH))
		return (0);
	if (parts_count == 1)
		return (0);
	return (1);
}
