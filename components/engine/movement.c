/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

static void	forward(void)
{
	if (get_value_map(get_cell(hero.pos_y), \
			get_cell((hero.pos_x + HERO_BODY * hero.cos_a))) == ' ')
		hero.pos_x += HERO_SPEED * hero.cos_a;
	if (get_value_map(get_cell((hero.pos_y + HERO_BODY * hero.sin_a)), \
				get_cell(hero.pos_x)) == ' ')
		hero.pos_y += HERO_SPEED * hero.sin_a;
}

static void	back(void)
{
	if (get_value_map(get_cell(hero.pos_y), \
			get_cell(hero.pos_x + (-HERO_BODY * hero.cos_a))) == ' ')
		hero.pos_x += -HERO_SPEED * hero.cos_a;
	if (get_value_map(get_cell((hero.pos_y + (-HERO_BODY * hero.sin_a))), \
				get_cell(hero.pos_x)) == ' ')
		hero.pos_y += -HERO_SPEED * hero.sin_a;
}

static void	left(void)
{
	if (get_value_map(get_cell(hero.pos_y), \
		get_cell((hero.pos_x + HERO_BODY * hero.sin_a))) == ' ')
		hero.pos_x += HERO_SPEED * hero.sin_a;
	if (get_value_map(get_cell((hero.pos_y + (-HERO_BODY * hero.cos_a))), \
				get_cell(hero.pos_x)) == ' ')
		hero.pos_y += -HERO_SPEED * hero.cos_a;
}

static void	right(void)
{
	if (get_value_map(get_cell(hero.pos_y), \
				get_cell((hero.pos_x + (-HERO_BODY * hero.sin_a)))) == ' ')
		hero.pos_x += -HERO_SPEED * hero.sin_a;
	if (get_value_map(get_cell((hero.pos_y + HERO_BODY * hero.cos_a)), \
				get_cell(hero.pos_x)) == ' ')
		hero.pos_y += HERO_SPEED * hero.cos_a;
}

void		movement(void)
{
	hero.sin_a = sin(hero.angle);
	hero.cos_a = cos(hero.angle);
	if (game.btn_pressed.w)
		forward();
	if (game.btn_pressed.s)
		back();
	if (game.btn_pressed.a)
		left();
	if (game.btn_pressed.d)
		right();
	if (game.btn_pressed.right)
		hero.angle += HERO_ROT_SPEED;
	if (game.btn_pressed.left)
		hero.angle -= HERO_ROT_SPEED;
}
