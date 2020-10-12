/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:21:00 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/12 16:14:29 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_set_raydir(t_game *game, int x, t_parse *parse)
{
	game->camerax = 2 * x / (double)parse->x_reso - 1;
	game->raydirx = game->dirx + game->planex * game->camerax;
	game->raydiry = game->diry + game->planey * game->camerax;
	game->mapx = (int)parse->spawn_point[1];
	game->mapy = (int)parse->spawn_point[0];
	game->deltadistx = fabs(1 / game->raydirx);
	game->deltadisty = fabs(1 / game->raydiry);
}

static void	ft_distance(t_game *game, t_parse *parse)
{
	if (game->raydirx < 0)
	{
		game->stepx = -1;
		game->sidedistx = (parse->spawn_point[1] - game->mapx) *
							game->deltadistx;
	}
	else
	{
		game->stepx = 1;
		game->sidedistx = (game->mapx + 1.0 - parse->spawn_point[1]) *
							game->deltadistx;
	}
	if (game->raydiry < 0)
	{
		game->stepy = -1;
		game->sidedisty = (parse->spawn_point[0] - game->mapy) *
							game->deltadisty;
	}
	else
	{
		game->stepy = 1;
		game->sidedisty = (game->mapy + 1.0 - parse->spawn_point[0]) *
							game->deltadisty;
	}
}

static int	ft_dda(t_game *game, t_parse *parse)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->sidedistx < game->sidedisty)
		{
			game->sidedistx += game->deltadistx;
			game->mapx += game->stepx;
			game->side = 0;
		}
		else
		{
			game->sidedisty += game->deltadisty;
			game->mapy += game->stepy;
			game->side = 1;
		}
		if (parse->map[game->mapy][game->mapx] == '1')
			hit = 1;
	}
	return (hit);
}

int			*ft_raycast(t_game *game, int *img_ptr, t_parse *parse)
{
	int		hit;
	int		x;
	double	zbuffer[parse->x_reso];

	x = -1;
	while (++x < parse->x_reso)
	{
		ft_set_raydir(game, x, parse);
		ft_distance(game, parse);
		hit = ft_dda(game, parse);
		if (game->side == 0)
			game->perpwalldist = (game->mapx - parse->spawn_point[1]
			+ (1 - game->stepx) / 2) / game->raydirx;
		else
			game->perpwalldist = (game->mapy - parse->spawn_point[0]
			+ (1 - game->stepy) / 2) / game->raydiry;
		game->lineheight = (int)(parse->y_reso / game->perpwalldist);
		ft_draw_screen(game, img_ptr, x, parse);
		zbuffer[x] = game->perpwalldist;
	}
	ft_sprite_draw(game, parse, zbuffer, img_ptr);
	return (img_ptr);
}
