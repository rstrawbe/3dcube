/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int		create_rgb(int r, int g, int b)
{
	int	t;

	t = 0;
	return (t << 24 | r << 16 | g << 8 | b);
}

int		get_dark_color(int color, double ratio)
{
	ratio = 1 - ratio;
	int t = (color >> 24) & 0xFF;
    int r = (int) (((color >> 16) & 0xFF) * ratio);
    int g = (int) (((color >> 8) & 0xFF) * ratio);
    int b = (int) ((color & 0xFF) * ratio);
    return (t << 24 | r << 16 | g << 8 | b);
}
