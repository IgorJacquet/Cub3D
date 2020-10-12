/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:55:32 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/12 16:20:50 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_sprite_dist(t_game *game, t_parse *parse)
{
	int i;
	int temp;

	i = -1;
	while (++i < parse->sprite_count)
	{
		game->sp_order[i] = i;
		parse->sprite[i].dist = ((parse->spawn_point[1] - parse->sprite[i].x) *
		(parse->spawn_point[1] - parse->sprite[i].x) + (parse->spawn_point[0] -
		parse->sprite[i].y) * (parse->spawn_point[0] - parse->sprite[i].y));
	}
	i = -1;
	while (++i < parse->sprite_count - 1)
	{
		if (parse->sprite[game->sp_order[i]].dist <
			parse->sprite[game->sp_order[i + 1]].dist)
		{
			temp = game->sp_order[i];
			game->sp_order[i] = game->sp_order[i + 1];
			game->sp_order[i + 1] = temp;
			i = -1;
		}
	}
	return (1);
}

void	ft_set_sp(t_sp_data *sp, t_parse *parse, int i, t_game *game)
{
	sp->spritex = parse->sprite[game->sp_order[i]].x - parse->spawn_point[1];
	sp->spritey = parse->sprite[game->sp_order[i]].y - parse->spawn_point[0];
	sp->invdet = 1.0 / (game->planex * game->diry - game->dirx * game->planey);
	sp->transformx = sp->invdet * (game->diry * sp->spritex -
						game->dirx * sp->spritey);
	sp->transformy = sp->invdet * (-game->planey * sp->spritex +
						game->planex * sp->spritey);
	sp->spritescreenx = (int)((parse->x_reso / 2) * (1 +
						sp->transformx / sp->transformy));
	sp->sp_height = abs((int)(parse->y_reso / (sp->transformy)));
	sp->drawstarty = -sp->sp_height / 2 + parse->y_reso / 2;
	if (sp->drawstarty < 0)
		sp->drawstarty = 0;
	sp->drawendy = sp->sp_height / 2 + parse->y_reso / 2;
	if (sp->drawendy >= parse->y_reso)
		sp->drawendy = parse->y_reso;
	sp->spritewidth = abs((int)(parse->y_reso / (sp->transformy)));
	sp->drawstartx = -sp->spritewidth / 2 + sp->spritescreenx;
	if (sp->drawstartx < 0)
		sp->drawstartx = 0;
	sp->drawendx = sp->spritewidth / 2 + sp->spritescreenx;
	if (sp->drawendx >= parse->x_reso)
		sp->drawendx = parse->x_reso;
}

void	ft_spd(t_game *g, double zbuffer[g->parse.x_reso],
										int *img_ptr, int stripe)
{
	int	y;
	int	d;

	while (++stripe < g->sp.drawendx)
	{
		g->sp.texx = (int)(256 * (stripe - (-g->sp.spritewidth / 2 +
g->sp.spritescreenx)) * g->data[4].width / g->sp.spritewidth) / 256;
		if (g->sp.transformy > 0 && stripe >= 0 && stripe <
		g->parse.x_reso && g->sp.transformy < zbuffer[stripe]
		&& (y = g->sp.drawstarty - 1))
			while (++y < g->sp.drawendy)
			{
				d = (y) * 256 - g->parse.y_reso * 128 + g->sp.sp_height * 128;
				g->sp.texy = ((d * g->data[4].height) / g->sp.sp_height) / 256;
				if (g->sp.texx < 0)
					g->sp.texx = 0;
				if (g->sp.texy < 0)
					g->sp.texy = 0;
				if ((his_get_color(&g->data[4], g->sp.texx,
				g->sp.texy) & 0x00ffffff) != 0)
					img_ptr[stripe + y * g->parse.x_reso] =
					his_get_color(&g->data[4], g->sp.texx, g->sp.texy);
			}
	}
}

void	ft_sprite_draw(t_game *game, t_parse *parse,
						double zbuffer[parse->x_reso], int *img_ptr)
{
	int	i;
	int stripe;

	i = -1;
	while (++i < parse->sprite_count)
	{
		ft_set_sp(&game->sp, &game->parse, i, game);
		stripe = game->sp.drawstartx - 1;
		ft_spd(game, zbuffer, img_ptr, stripe);
	}
}

void	ft_sprite_data(t_parse *parse)
{
	int x;
	int y;
	int i;

	i = 0;
	y = 0;
	while (parse->map[++y] && parse->map[y][0])
	{
		x = 0;
		while (parse->map[y][++x])
			if (parse->map[y][x] == '2')
			{
				parse->sprite[i].x = x + 0.5;
				parse->sprite[i].y = y + 0.5;
				i++;
			}
	}
}
