/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:21:00 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/09 19:12:40 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_set_raydir(t_game *game, int x, t_parse *parse)
{
	game->cameraX = 2 * x / (double)parse->x_reso - 1;
	game->rayDirX = game->dirX + game->planeX * game->cameraX;
	game->rayDirY = game->dirY + game->planeY * game->cameraX;
	game->mapX = (int)parse->spawn_point[1];
	game->mapY = (int)parse->spawn_point[0];
	game->deltaDistX = fabs(1 / game->rayDirX);
	game->deltaDistY = fabs(1 / game->rayDirY);
}

int				his_get_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

static void	ft_distance(t_game *game, t_parse *parse)
{
	if (game->rayDirX < 0)
	{
		game->stepX = -1;
		game->sideDistX = (parse->spawn_point[1] - game->mapX) *
							game->deltaDistX;
	}
	else
	{
		game->stepX = 1;
		game->sideDistX = (game->mapX + 1.0 - parse->spawn_point[1]) *
							game->deltaDistX;
	}
	if (game->rayDirY < 0)
	{
		game->stepY = -1;
		game->sideDistY = (parse->spawn_point[0] - game->mapY) *
							game->deltaDistY;
	}
	else
	{
		game->stepY = 1;
		game->sideDistY = (game->mapY + 1.0 - parse->spawn_point[0]) *
							game->deltaDistY;
	}
}

static int		ft_dda(t_game *game, t_parse *parse)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (game->sideDistX < game->sideDistY)
		{
			game->sideDistX += game->deltaDistX;
			game->mapX += game->stepX;
			game->side = 0;
		}
		else
		{
			game->sideDistY += game->deltaDistY;
			game->mapY += game->stepY;
			game->side = 1;
		}
		if (parse->map[game->mapY][game->mapX] == '1')
			hit = 1;
	}
	return (hit);
}

int				ft_sprite_dist(t_game *game, t_parse *parse)
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

void			ft_set_sp(t_sp_data *sp, t_parse *parse, int i, t_game *game)
{
	sp->spriteX = parse->sprite[game->sp_order[i]].x - parse->spawn_point[1];
	sp->spriteY = parse->sprite[game->sp_order[i]].y - parse->spawn_point[0];
	sp->invDet = 1.0 / (game->planeX * game->dirY - game->dirX * game->planeY);
	sp->transformX = sp->invDet * (game->dirY * sp->spriteX -
						game->dirX * sp->spriteY);
	sp->transformY = sp->invDet * (-game->planeY * sp->spriteX +
						game->planeX * sp->spriteY);
	sp->spriteScreenX = (int)((parse->x_reso / 2) * (1 +
						sp->transformX / sp->transformY));
	sp->spriteHeight = abs((int)(parse->y_reso / (sp->transformY)));
	sp->drawStartY = -sp->spriteHeight / 2 + parse->y_reso / 2;
	if (sp->drawStartY < 0)
		sp->drawStartY = 0;
	sp->drawEndY = sp->spriteHeight / 2 + parse->y_reso / 2;
	if (sp->drawEndY >= parse->y_reso)
		sp->drawEndY = parse->y_reso;
	sp->spriteWidth = abs((int)(parse->y_reso / (sp->transformY)));
	sp->drawStartX = -sp->spriteWidth / 2 + sp->spriteScreenX;
	if (sp->drawStartX < 0)
		sp->drawStartX = 0;
	sp->drawEndX = sp->spriteWidth / 2 + sp->spriteScreenX;
	if (sp->drawEndX >= parse->x_reso)
		sp->drawEndX = parse->x_reso;
}

void			ft_sprite_draw(t_game *game, t_parse *parse, double zbuffer[parse->x_reso], int *img_ptr)
{
	int	i;
	int	j;

	i = -1;

	while (++i < parse->sprite_count)
	{
		ft_set_sp(&game->sp, &game->parse, i, game);
		for(int stripe = game->sp.drawStartX; stripe < game->sp.drawEndX; stripe++)
		{
			game->sp.texX = (int)(256 * (stripe - (-game->sp.spriteWidth / 2 + game->sp.spriteScreenX)) * game->data[4].width / game->sp.spriteWidth) / 256;
			if(game->sp.transformY > 0 && stripe >= 0 && stripe < parse->x_reso && game->sp.transformY < zbuffer[stripe])
				for(int y = game->sp.drawStartY; y < game->sp.drawEndY; y++)
				{
					int d = (y) * 256 - parse->y_reso * 128 + game->sp.spriteHeight * 128;
					game->sp.texY = ((d * game->data[4].height) / game->sp.spriteHeight) / 256;
					if (game->sp.texX < 0)
						game->sp.texX = 0;
					if (game->sp.texY < 0)
						game->sp.texY = 0;
					if((his_get_color(&game->data[4], game->sp.texX, game->sp.texY) & 0x00FFFFFF) != 0)
						img_ptr[stripe + y * parse->x_reso] = his_get_color(&game->data[4], game->sp.texX, game->sp.texY);
				}
		}
	}
}

static void		ft_draw_screen(t_game *game, int *img_ptr, int x, t_parse *parse)
{
	int drawStart;
	int i;

	i = 0;
	drawStart = -game->lineHeight / 2 + parse->y_reso / 2;
	if(drawStart < 0)
		drawStart = 0;
	int drawEnd = game->lineHeight / 2 + parse->y_reso / 2;
	if(drawEnd >= parse->y_reso)
		drawEnd = parse->y_reso;
	double wallX;
	if (game->side == 0) wallX = parse->spawn_point[0] + game->perpWallDist * game->rayDirY;
	else           wallX = parse->spawn_point[1] + game->perpWallDist * game->rayDirX;
	wallX -= floor((wallX));
	int texX = (int)(wallX * (double)(game->data[0].width));
	if(game->side == 0 && game->rayDirX < 0) 
		texX = game->data[0].width - texX - 1;
	if(game->side == 1 && game->rayDirY > 0) 
		texX = game->data[0].width - texX - 1;
	double step = 1.0 * game->data[0].height / game->lineHeight;
	double texPos = (drawStart - parse->y_reso / 2 + game->lineHeight / 2) * step;
	while (i < drawStart)
		img_ptr[x + (i++ * parse->x_reso)] = create_trgb(0, parse, 0);
	if (game->side == 0 && game->rayDirX >= 0)
	{
		while (i < drawEnd)
		{
			int texY = (int)texPos & (game->data[0].height - 1);
			texPos += step;
			img_ptr[x + i++ * parse->x_reso] = his_get_color(&game->data[0], texX, texY);
		}
	}
	else if (game->side == 0 && game->rayDirX < 0) //mur E
		while (i < drawEnd)
		{	
			int texY = (int)texPos & (game->data[1].height - 1);
			texPos += step;
			img_ptr[x + i++ * parse->x_reso] = his_get_color(&game->data[1], texX, texY);
		}
	else if (game->side && game->rayDirY >= 0) //mur N
		while (i < drawEnd)
		{
			int texY = (int)texPos & (game->data[2].height - 1);
			texPos += step;
			img_ptr[x + i++ * parse->x_reso] = his_get_color(&game->data[2], texX, texY);
		}
	else if (game->side && game->rayDirY < 0) //mur S
		while (i < drawEnd)
		{
			int texY = (int)texPos & (game->data[3].height - 1);
			texPos += step;
			img_ptr[x + i++ * parse->x_reso] = his_get_color(&game->data[3], texX, texY);
		}
	i = -1; 
	while (++i < parse->y_reso - drawEnd)
		img_ptr[x + (drawEnd + i) * parse->x_reso] = create_trgb(0, parse, 1);
}

int				*ft_raycast(t_game *game, int *img_ptr, t_parse *parse)
{
	int hit;
	int x;
	double  zbuffer[parse->x_reso];

	x = -1;
	while(++x < parse->x_reso)
	{
		ft_set_raydir(game, x, parse);
		ft_distance(game, parse);
		hit = ft_dda(game, parse);
		if(game->side == 0) 
			game->perpWallDist = (game->mapX - parse->spawn_point[1] + (1 - game->stepX) / 2) / game->rayDirX;
		else
			game->perpWallDist = (game->mapY - parse->spawn_point[0] + (1 - game->stepY) / 2) / game->rayDirY;    
		game->lineHeight = (int)(parse->y_reso / game->perpWallDist);
		ft_draw_screen(game, img_ptr, x, parse);
		zbuffer[x] = game->perpWallDist;
	}
	ft_sprite_draw(game, parse, zbuffer, img_ptr);
	return (img_ptr);
}