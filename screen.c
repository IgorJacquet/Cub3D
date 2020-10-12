/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:11:34 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/12 16:34:06 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_draw_text(t_game *game, int x, int *img_ptr, int n)
{
	int i;
	int	texy;

	i = game->screen.drawstart;
	while (i < game->screen.drawend)
	{
		texy = (int)game->screen.texpos & (game->data[1].height - 1);
		game->screen.texpos += game->screen.step;
		img_ptr[x + i++ * game->parse.x_reso] = his_get_color(&game->data[n],
													game->screen.texx, texy);
	}
}

static void	ft_screen_set(t_game *game, t_parse *parse)
{
	double	wallx;

	game->screen.drawstart = -game->lineheight / 2 + parse->y_reso / 2;
	if (game->screen.drawstart < 0)
		game->screen.drawstart = 0;
	game->screen.drawend = game->lineheight / 2 + parse->y_reso / 2;
	if (game->screen.drawend >= parse->y_reso)
		game->screen.drawend = parse->y_reso;
	if (game->side == 0)
		wallx = parse->spawn_point[0] + game->perpwalldist * game->raydiry;
	else
		wallx = parse->spawn_point[1] + game->perpwalldist * game->raydirx;
	wallx -= floor((wallx));
	game->screen.texx = (int)(wallx * (double)(game->data[0].width));
	if (game->side == 0 && game->raydirx < 0)
		game->screen.texx = game->data[0].width - game->screen.texx - 1;
	if (game->side == 1 && game->raydiry > 0)
		game->screen.texx = game->data[0].width - game->screen.texx - 1;
	game->screen.step = 1.0 * game->data[0].height / game->lineheight;
	game->screen.texpos = (game->screen.drawstart - parse->y_reso / 2 +
							game->lineheight / 2) * game->screen.step;
}

void		ft_draw_screen(t_game *game, int *img_ptr, int x, t_parse *parse)
{
	int	i;

	i = 0;
	ft_screen_set(game, parse);
	while (i < game->screen.drawstart)
		img_ptr[x + (i++ * parse->x_reso)] = create_trgb(0, parse, 0);
	if (game->side == 0 && game->raydirx >= 0)
		ft_draw_text(game, x, img_ptr, 0);
	else if (game->side == 0 && game->raydirx < 0)
		ft_draw_text(game, x, img_ptr, 1);
	else if (game->side && game->raydiry >= 0)
		ft_draw_text(game, x, img_ptr, 2);
	else if (game->side && game->raydiry < 0)
		ft_draw_text(game, x, img_ptr, 3);
	i = -1;
	while (++i < parse->y_reso - game->screen.drawend)
		img_ptr[x + (game->screen.drawend + i) * parse->x_reso] =
		create_trgb(0, parse, 1);
}
