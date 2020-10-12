/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:55:32 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/12 19:28:47 by ijacquet         ###   ########.fr       */
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

void	ft_sp_draw(t_game *game, t_parse *parse, int *img_ptr
					, int stripe)
{
	int y;
	int d;

	y = game->sp.drawstarty - 1;
	while (++y < game->sp.drawendy)
	{
		d = (y) * 256 - parse->y_reso * 128 + game->sp.sp_height * 128;
		game->sp.texy = ((d * game->data[4].height) / game->sp.sp_height) / 256;
		if (game->sp.texx < 0)
			game->sp.texx = 0;
		if (game->sp.texy < 0)
			game->sp.texy = 0;
		if ((his_get_color(&game->data[4], game->sp.texx, game->sp.texy)
													& 0x00ffffff) != 0)
			img_ptr[stripe + y * parse->x_reso] = his_get_color(&game->data[4],
												game->sp.texx, game->sp.texy);
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
		while (++stripe < game->sp.drawendx)
		{
			game->sp.texx = (int)(256 * (stripe - (-game->sp.spritewidth / 2 +
game->sp.spritescreenx)) * game->data[4].width / game->sp.spritewidth) / 256;
			if (game->sp.transformy > 0 && stripe >= 0 && stripe <
				parse->x_reso && game->sp.transformy < zbuffer[stripe])
				ft_sp_draw(game, parse, img_ptr, stripe);
		}
	}
}
