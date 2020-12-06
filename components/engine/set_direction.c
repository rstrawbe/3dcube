/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	set_direction(char c)
{
	hero.angle = (c == 'N') ? 3 * M_PI / 2 : 0;
	hero.angle = (c == 'W') ? M_PI : hero.angle;
	hero.angle = (c == 'S') ? M_PI / 2 : hero.angle;
	hero.angle = (c == 'E') ? 0 : hero.angle;
	hero.direction = c;
}
