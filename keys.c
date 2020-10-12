/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:23:59 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/12 16:28:42 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_key_pressed(int key, t_game *game)
{
	if (key == KEY_UP || key == KEY_W)
		game->forback = 1;
	else if (key == KEY_DOWN || key == KEY_S)
		game->forback = -1;
	else if (key == KEY_A)
		game->leftright = -1;
	else if (key == KEY_D)
		game->leftright = 1;
	else if (key == KEY_LEFT)
		game->turn = -1;
	else if (key == KEY_RIGHT)
		game->turn = 1;
	if (key == KEY_ESC)
		ft_free_exit(game);
	return (0);
}

int		ft_key_released(int key, t_game *game)
{
	if (key == KEY_UP || key == KEY_W)
		game->forback = 0;
	else if (key == KEY_DOWN || key == KEY_S)
		game->forback = 0;
	else if (key == KEY_A)
		game->leftright = 0;
	else if (key == KEY_D)
		game->leftright = 0;
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		game->turn = 0;
	return (1);
}
