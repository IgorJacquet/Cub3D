/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:21:29 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/12 16:22:23 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		move_fw(t_game *game, t_parse *parse)
{
	double	space_y;
	double	space_x;
	int		r;

	space_y = (game->diry >= 0) ? 0.2 : -0.2;
	space_x = (game->dirx >= 0) ? 0.2 : -0.2;
	if (parse->map[(int)(parse->spawn_point[0] - space_y)][(int)(space_x *
		game->forback + parse->spawn_point[1] + (game->dirx * MV_SPD *
		game->forback))] != '1' && parse->map[(int)(parse->spawn_point[0] +
		space_y)][(int)(space_x * game->forback + parse->spawn_point[1] +
		(game->dirx * MV_SPD * game->forback))] != '1')
		parse->spawn_point[1] += game->dirx * game->forback * MV_SPD;
	if (parse->map[(int)(space_y * game->forback + (parse->spawn_point[0] +
		game->diry * MV_SPD * game->forback))][(int)(parse->spawn_point[1] +
		space_x)] != '1' && parse->map[(int)(space_y * game->forback +
		(parse->spawn_point[0] + game->diry * MV_SPD * game->forback))]
		[(int)(parse->spawn_point[1] - space_x)] != '1')
		parse->spawn_point[0] += game->diry * MV_SPD * game->forback;
	r = ft_sprite_dist(game, &game->parse);
	return (r);
}

int		move_lr(t_game *game, t_parse *parse)
{
	double	space_y;
	double	space_x;
	int		r;

	space_y = (game->diry >= 0) ? 0.2 : -0.2;
	space_x = (game->dirx >= 0) ? 0.2 : -0.2;
	if (parse->map[(int)(parse->spawn_point[0] + space_y)][(int)
		(parse->spawn_point[1] - game->leftright * game->diry * MV_SPD - space_y
		* game->leftright)] != '1' && parse->map[(int)(parse->spawn_point[0] -
		space_y)][(int)(parse->spawn_point[1] - game->leftright * game->diry *
		MV_SPD - space_y * game->leftright)] != '1')
		parse->spawn_point[1] -= game->leftright * game->diry * MV_SPD;
	if (parse->map[(int)(parse->spawn_point[0] + game->leftright * game->dirx *
MV_SPD + space_x * game->leftright)][(int)(parse->spawn_point[1] + space_x)] !=
'1' && parse->map[(int)(parse->spawn_point[0] + game->leftright * game->dirx *
MV_SPD + space_x * game->leftright)][(int)(parse->spawn_point[1] - space_x)])
		parse->spawn_point[0] += game->leftright * game->dirx * MV_SPD;
	r = ft_sprite_dist(game, &game->parse);
	return (r);
}

int		move_turn(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	turn_spd;

	old_dir_x = game->dirx;
	old_plane_x = game->planex;
	turn_spd = game->turn * MV_SPD / 2;
	game->dirx = game->dirx * cos(turn_spd) - game->diry * sin(turn_spd);
	game->diry = old_dir_x * sin(turn_spd) + game->diry * cos(turn_spd);
	game->planex = game->planex * cos(turn_spd) - game->planey * sin(turn_spd);
	game->planey = old_plane_x * sin(turn_spd) + game->planey * cos(turn_spd);
	return (1);
}
