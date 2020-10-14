/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:11:34 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/14 14:46:59 by ijacquet         ###   ########.fr       */
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
		texy = (int)game->screen.texpos & (game->data[n].height - 1);
		game->screen.texpos += game->screen.step;
		img_ptr[x + i++ * game->parse.x_reso] = his_get_color(&game->data[n],
													game->screen.texx, texy);
	}
}

int			ft_text_select(int side, double raydirx, double raydiry)
{
	if (side == 0 && raydirx >= 0)
		return (0);
	else if (side == 0 && raydirx < 0)
		return (1);
	else if (side && raydiry >= 0)
		return (2);
	else if (side && raydiry < 0)
		return (3);
	return (21);
}

static void	ft_screen_set(t_game *game, t_parse *parse, int n)
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
	game->screen.texx = (int)(wallx * (double)(game->data[n].width));
	if (game->side == 0 && game->raydirx < 0)
		game->screen.texx = game->data[n].width - game->screen.texx - 1;
	if (game->side == 1 && game->raydiry > 0)
		game->screen.texx = game->data[n].width - game->screen.texx - 1;
	game->screen.step = 1.0 * game->data[n].height / game->lineheight;
	game->screen.texpos = (game->screen.drawstart - parse->y_reso / 2 +
							game->lineheight / 2) * game->screen.step;
}

void		ft_draw_screen(t_game *game, int *img_ptr, int x, t_parse *parse)
{
	int	i;
	int n;

	i = 0;
	n = ft_text_select(game->side, game->raydirx, game->raydiry);
	ft_screen_set(game, parse, n);
	while (i < game->screen.drawstart)
		img_ptr[x + (i++ * parse->x_reso)] = create_trgb(0, parse, 0);
	ft_draw_text(game, x, img_ptr, n);
	i = -1;
	while (++i < parse->y_reso - game->screen.drawend)
		img_ptr[x + (game->screen.drawend + i) * parse->x_reso] =
		create_trgb(0, parse, 1);
}
