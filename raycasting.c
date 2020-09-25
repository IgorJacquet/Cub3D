/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:21:00 by ijacquet          #+#    #+#             */
/*   Updated: 2020/09/25 18:02:45 by ijacquet         ###   ########.fr       */
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

int        ft_sprite_dist(t_game *game)
{
    int i;
    int temp;

    i = -1;
    printf("lol\n");
    if (!(game->sp_order = malloc(sizeof(int *) * (game->sprite_count))))
        return(0);
    while (++i < game->sprite_count)
    {
        game->sp_order[i] = i;
        game->sprite[i].dist = ((game->spawn_point[1] - game->sprite[i].x) * (game->spawn_point[1] - game->sprite[i].x) + (game->spawn_point[0] - game->sprite[i].y) * (game->spawn_point[0] - game->sprite[i].y));
    }
    i = -1;
    while (++i < game->sprite_count - 1)
    {       
        if (game->sprite[game->sp_order[i]].dist < game->sprite[game->sp_order[i + 1]].dist)
        {
            temp = game->sp_order[i];
            game->sp_order[i] = game->sp_order[i + 1];
            game->sp_order[i + 1] = temp;
            i = -1;
        }
    }
    for (int i = 0; i < game->sprite_count; i++)
        printf("dist : %f, %d\n", game->sprite[game->sp_order[i]].dist, i);
    printf("\n");
    return (1);
}

int     ft_sprite_draw(t_game *game, double zbuffer[game->x_reso], int *img_ptr)
{
    for(int i = 0; i < game->sprite_count; i++)
    {
        //translate sprite position to relative to camera
        double spriteX = game->sprite[game->sp_order[i]].x - game->spawn_point[1];
        double spriteY = game->sprite[game->sp_order[i]].y - game->spawn_point[0];
        double invDet = 1.0 / (game->planeX * game->dirY - game->dirX * game->planeY); //required for correct matrix multiplication

        double transformX = invDet * (game->dirY * spriteX - game->dirX * spriteY);
        double transformY = invDet * (-game->planeY * spriteX + game->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

        int spriteScreenX = (int)((game->x_reso / 2) * (1 + transformX / transformY));

        //calculate height of the sprite on screen
        int spriteHeight = abs((int)(game->y_reso / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
        //calculate lowest and highest pixel to fill in current stripe
        int drawStartY = -spriteHeight / 2 + game->y_reso / 2;
        if(drawStartY < 0) drawStartY = 0;
        int drawEndY = spriteHeight / 2 + game->y_reso / 2;
        if(drawEndY >= game->y_reso) drawEndY = game->y_reso - 1;

        //calculate width of the sprite
        int spriteWidth = abs((int)(game->y_reso / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if(drawStartX < 0) drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if(drawEndX >= game->x_reso) drawEndX = game->x_reso - 1;

        //loop through every vertical stripe of the sprite on screen
        for(int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * game->data[4].width / spriteWidth) / 256;
            //the conditions in the if are:
            //1) it's in front of camera plane so you don't see things behind you
            //2) it's on the screen (left)
            //3) it's on the screen (right)
            //4) ZBuffer, with perpendicular distance
            if(transformY > 0 && stripe > 0 && stripe < game->x_reso && transformY < zbuffer[stripe])
            for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
            {
                int d = (y) * 256 - game->y_reso * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
                int texY = ((d * game->data[4].height) / spriteHeight) / 256;
                if (texX < 0)
                    texX = 0;
                if (texY < 0)
                    texY = 0;
                if((his_get_color(&game->data[4], texX, texY) & 0x00FFFFFF) != 0)
                    img_ptr[stripe + y * game->x_reso] = his_get_color(&game->data[4], texX, texY);
            }
        }
    }
    return (1);
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
    double wallX;
    if (game->side == 0) wallX = game->spawn_point[0] + game->perpWallDist * game->rayDirY;
    else           wallX = game->spawn_point[1] + game->perpWallDist * game->rayDirX;
    wallX -= floor((wallX));
    int texX = (int)(wallX * (double)(game->data[0].width));
    if(game->side == 0 && game->rayDirX > 0) 
        texX = game->data[0].width - texX - 1;
    if(game->side == 1 && game->rayDirY < 0) 
        texX = game->data[0].width - texX - 1;
    double step = 1.0 * game->data[0].height / game->lineHeight;
    double texPos = (drawStart - game->y_reso / 2 + game->lineHeight / 2) * step;
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
            int texY = (int)texPos & (game->data[1].height - 1);
            texPos += step;
            img_ptr[x + i++ * game->x_reso] = his_get_color(&game->data[1], texX, texY);
        }
    else if (game->side && game->rayDirY >= 0) //mur N
        while (i < drawEnd)
        {
            int texY = (int)texPos & (game->data[2].height - 1);
            texPos += step;
            img_ptr[x + i++ * game->x_reso] = his_get_color(&game->data[2], texX, texY);
        }
    else if (game->side && game->rayDirY < 0) //mur S
        while (i < drawEnd)
        {
            int texY = (int)texPos & (game->data[3].height - 1);
            texPos += step;
            img_ptr[x + i++ * game->x_reso] = his_get_color(&game->data[3], texX, texY);
        }    i = -1; 
    while (++i < game->y_reso - drawEnd)
        img_ptr[x + (drawEnd + i) * game->x_reso] = create_trgb(0, game, 1);
}

int   *ft_raycast(t_game *game, int *img_ptr)
{
    int hit;
    int x;
    double  zbuffer[game->x_reso];

    x = -1;
    while(++x < game->x_reso)
    {
        ft_set_raydir(game, x);
        ft_distance(game);
        hit = ft_dda(game);
        if(game->side == 0) 
            game->perpWallDist = (game->mapX - game->spawn_point[1] + (1 - game->stepX) / 2) / game->rayDirX;
        else
            game->perpWallDist = (game->mapY - game->spawn_point[0] + (1 - game->stepY) / 2) / game->rayDirY;    
        game->lineHeight = (int)(game->y_reso / game->perpWallDist);
        ft_draw_screen(game, img_ptr, x);
        zbuffer[x] = game->perpWallDist;
    }
    ft_sprite_draw(game, zbuffer, img_ptr);
    return (img_ptr);
}
