/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:21:00 by ijacquet          #+#    #+#             */
/*   Updated: 2020/09/17 15:31:21 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void    ft_set_raydir(t_game *game, int x)
{
    game->cameraX = 2 * x / (double)game->x_reso - 1;
    game->rayDirX = game->dirX + game->planeX * game->cameraX;
    game->rayDirY = game->dirY + game->planeY * game->cameraX;
    game->mapX = (int)game->spawn_point[1];
    game->mapY = (int)game->spawn_point[0];
    game->deltaDistX = fabs(1 / game->rayDirX);
    game->deltaDistY = fabs(1 / game->rayDirY);
}

void            his_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int            his_get_color(t_data *data, int x, int y)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    return (*(unsigned int*)dst);
}

static void    ft_distance(t_game *game)
{
    if(game->rayDirX < 0)
    {
        game->stepX = -1;
        game->sideDistX = (game->spawn_point[1] - game->mapX) * game->deltaDistX;
    }
    else
    {
        game->stepX = 1;
        game->sideDistX = (game->mapX + 1.0 - game->spawn_point[1]) * game->deltaDistX;
    }
    if(game->rayDirY < 0)
    {
        game->stepY = -1;
        game->sideDistY = (game->spawn_point[0] - game->mapY) * game->deltaDistY;
    }
    else
    {
        game->stepY = 1;
        game->sideDistY = (game->mapY + 1.0 - game->spawn_point[0]) * game->deltaDistY;
    }
}

static int     ft_dda(t_game *game)
{
    int hit;
    
    hit = 0;
    while (hit == 0)
    {
        if(game->sideDistX < game->sideDistY)
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
        if(game->map[game->mapY][game->mapX] == '1')
            hit = 1;
    }
    return (hit);
}

static void    ft_draw_screen(t_game *game, int *img_ptr, int x)
{
    int drawStart;
    int i;
    
    i = 0;
    drawStart = -game->lineHeight / 2 + game->y_reso / 2;
    if(drawStart < 0)
        drawStart = 0;
    int drawEnd = game->lineHeight / 2 + game->y_reso / 2;
    if(drawEnd >= game->y_reso)
        drawEnd = game->y_reso;

    //texturing calculations
//      int texNum = game->map[game->mapX][game->mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (game->side == 0) wallX = game->spawn_point[0] + game->perpWallDist * game->rayDirY;
      else           wallX = game->spawn_point[1] + game->perpWallDist * game->rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(game->data[0].width));
      if(game->side == 0 && game->rayDirX > 0) texX = game->data[0].width - texX - 1;
      if(game->side == 1 && game->rayDirY < 0) texX = game->data[0].width - texX - 1;

    // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * game->data[0].height / game->lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - game->y_reso / 2 + game->lineHeight / 2) * step;

      for(int y = drawStart; y<drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
      }
    while (i < drawStart)
        img_ptr[x + (i++ * game->x_reso)] = create_trgb(0, game, 0);
    if (game->side == 0 && game->rayDirX >= 0) // mur W
    {
        while (i < drawEnd)
        {
            int texY = (int)texPos & (game->data[0].height - 1);
            texPos += step;
            img_ptr[x + i++ * game->x_reso] = his_get_color(&game->data[0], texX, texY);
        }
    }
    else if (game->side == 0 && game->rayDirX < 0) //mur E
        while (i < drawEnd)

        {
            int texY = (int)texPos & (game->data[0].height - 1);
            texPos += step;
            img_ptr[x + i++ * game->x_reso] = his_get_color(&game->data[0], texX, texY);
        }
    else if (game->side && game->rayDirY >= 0) //mur N
        while (i < drawEnd)

        {
            int texY = (int)texPos & (game->data[0].height - 1);
            texPos += step;
            img_ptr[x + i++ * game->x_reso] = his_get_color(&game->data[0], texX, texY);
        }
    else if (game->side && game->rayDirY < 0) //mur S
        while (i < drawEnd)

        {
            int texY = (int)texPos & (game->data[0].height - 1);
            texPos += step;
            img_ptr[x + i++ * game->x_reso] = his_get_color(&game->data[0], texX, texY);
        }    i = -1; 
    while (++i < game->y_reso - drawEnd)
        img_ptr[x + (drawEnd + i) * game->x_reso] = create_trgb(0, game, 1);
}

int   *ft_raycast(t_game *game, int *img_ptr)
{
    int hit;
    int x;

    x = -1;
    while(++x <game->x_reso)
    {
		printf("%p\n", (int*)game->data[5].addr);
        ft_set_raydir(game, x);
        ft_distance(game);
        hit = ft_dda(game);
        if(game->side == 0) 
            game->perpWallDist = (game->mapX - game->spawn_point[1] + (1 - game->stepX) / 2) / game->rayDirX;
        else
            game->perpWallDist = (game->mapY - game->spawn_point[0] + (1 - game->stepY) / 2) / game->rayDirY;    
        game->lineHeight = (int)(game->y_reso / game->perpWallDist);
        ft_draw_screen(game, img_ptr, x);
    }
    return (img_ptr);
}
