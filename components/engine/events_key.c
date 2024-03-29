/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstrawbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 19:30:33 by rstrawbe          #+#    #+#             */
/*   Updated: 2020/08/07 23:27:45 by rstrawbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

int	on_key_release(int keycode)
{
	if ((keycode == CODE_KEY_W) || (keycode == CODE_KEY_W_LIN))
		game.btn_pressed.w = 0;
	if ((keycode == CODE_KEY_S) || (keycode == CODE_KEY_S_LIN))
		game.btn_pressed.s = 0;
	if ((keycode == CODE_KEY_A) || (keycode == CODE_KEY_A_LIN))
		game.btn_pressed.a = 0;
	if ((keycode == CODE_KEY_D) || (keycode == CODE_KEY_D_LIN))
		game.btn_pressed.d = 0;
	if ((keycode == CODE_KEY_RIGHT) || (keycode == CODE_KEY_RIGHT_LIN))
		game.btn_pressed.right = 0;
	if ((keycode == CODE_KEY_LEFT) || (keycode == CODE_KEY_LEFT_LIN))
		game.btn_pressed.left = 0;
	return (0);
}

int	on_key_press_handler(int keycode)
{
	if ((keycode == CODE_KEY_W) || (keycode == CODE_KEY_W_LIN))
		game.btn_pressed.w = 1;
	if ((keycode == CODE_KEY_S) || (keycode == CODE_KEY_S_LIN))
		game.btn_pressed.s = 1;
	if ((keycode == CODE_KEY_A) || (keycode == CODE_KEY_A_LIN))
		game.btn_pressed.a = 1;
	if ((keycode == CODE_KEY_D) || (keycode == CODE_KEY_D_LIN))
		game.btn_pressed.d = 1;
	if ((keycode == CODE_KEY_RIGHT) || (keycode == CODE_KEY_RIGHT_LIN))
		game.btn_pressed.right = 1;
	if ((keycode == CODE_KEY_LEFT) || (keycode == CODE_KEY_LEFT_LIN))
		game.btn_pressed.left = 1;
	if ((keycode == CODE_KEY_ESC) || (keycode == CODE_KEY_ESC_LIN))
	{
		mlx_destroy_window(vars.mlx, vars.win);
		exit(0);
	}
	return (1);
}
