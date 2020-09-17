/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:14:42 by ijacquet          #+#    #+#             */
/*   Updated: 2020/09/17 16:10:29 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double MV_SPD = 0.05;

int    create_trgb(int t, t_game *game, int i)
{
    if (i == 0)
        return(t << 24 | game->ceiling_red << 16 | game->ceiling_green << 8   \
        | game->ceiling_blue);
	else
        return(t << 24 | game->floor_red << 16 | game->floor_green << 8   \
        | game->floor_blue);
}

int		move_fw(t_game *game)
{
	double space_Y;
	double space_X;

	space_Y = (game->dirY >= 0) ? 0.2 : -0.2;
	space_X = (game->dirX >= 0) ? 0.2 : -0.2;
	if (game->map[(int)(game->spawn_point[0] - space_Y)][(int)(space_X * \
		game->forback + game->spawn_point[1] + (game->dirX * MV_SPD * \
		game->forback))] != '1' && game->map[(int)(game->spawn_point[0] + \
		space_Y)][(int)(space_X * game->forback + game->spawn_point[1] + \
		(game->dirX * MV_SPD * game->forback))] != '1')
		game->spawn_point[1] += game->dirX * MV_SPD * game->forback;
	if (game->map[(int)(space_Y * game->forback + (game->spawn_point[0] + game->dirY * MV_SPD * game->forback))][(int)(game->spawn_point[1] + space_X)] != '1' && game->map[(int)(space_Y * game->forback + (game->spawn_point[0] + game->dirY * MV_SPD * game->forback))][(int)(game->spawn_point[1] - space_X)] != '1')
		game->spawn_point[0] += game->dirY * MV_SPD * game->forback;
	return (1);
}

int			move_lr(t_game *game)
{
	double space_Y;
	double space_X;

	space_Y = (game->dirY >= 0) ? 0.2 : -0.2;
	space_X = (game->dirX >= 0) ? 0.2 : -0.2;
	if (game->map[(int)(game->spawn_point[0] + space_Y)][(int)(game->spawn_point[1] - game->leftright * game->dirY * MV_SPD - space_Y * game->leftright)] != '1' && game->map[(int)(game->spawn_point[0] - space_Y)][(int)(game->spawn_point[1] - game->leftright * game->dirY * MV_SPD - space_Y * game->leftright)] != '1')
	{
		printf("%f\n", game->spawn_point[1]);
		game->spawn_point[1] -= game->leftright * game->dirY * MV_SPD;
	}
	if (game->map[(int)(game->spawn_point[0] + game->leftright * game->dirX * MV_SPD + space_X * game->leftright)][(int)(game->spawn_point[1] + space_X)] != '1' && game->map[(int)(game->spawn_point[0] + game->leftright * game->dirX * MV_SPD + space_X * game->leftright)][(int)(game->spawn_point[1] - space_X)])
	{
		printf("%f\n", game->spawn_point[0]);
		game->spawn_point[0] += game->leftright * game->dirX * MV_SPD;
	}
	return (1);
	
}

int			move_turn(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	turn_spd;

	old_dir_x = game->dirX;
	old_plane_x = game->planeX;
	turn_spd = game->turn * MV_SPD / 2;
	game->dirX = game->dirX * cos(turn_spd) - game->dirY * sin(turn_spd);
	game->dirY = old_dir_x * sin(turn_spd) + game->dirY * cos(turn_spd);
	game->planeX = game->planeX * cos(turn_spd) - game->planeY * sin(turn_spd);
	game->planeY = old_plane_x * sin(turn_spd) + game->planeY * cos(turn_spd);
	return (1);
}

int				key_pressed(int key, t_game *game)
{
	if (key == KEY_UP || key == KEY_W)
		game->forback = 1;
	else if (key == KEY_DOWN || key == KEY_S)
		game->forback = -1;
	else if (key == KEY_A)
		game->leftright = -1;
	else if (key == KEY_D)
		game->leftright = 1;
	else if(key == KEY_LEFT)
		game->turn = -1;
	else if(key == KEY_RIGHT)
		game->turn = 1;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->window);
		exit(0);
	}
	return (0);
}

int				key_released(int key, t_game *game)
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

int				ft_loop(t_game *game)
{
	static int		next = 1;

	if (next)
	{
		ft_raycast(game, (int *)game->data[5].addr);
		mlx_put_image_to_window (game->mlx, game->window, game->data[5].img, 0, 0);
		next = 0;
	}
	if (game->forback)
		next = move_fw(game);
	if (game->leftright)
		next = move_lr(game);
	if (game->turn)
		next = move_turn(game);
	return (1);
}

void	*ft_image(t_parse *parse, t_game *game)
{
	game->data[5].img = mlx_new_image(game->mlx, parse->x_reso, parse->y_reso);
	game->data[5].addr = mlx_get_data_addr(game->data[5].img, &game->data[5].bits_per_pixel, &game->data[5].line_length, &game->data[5].endian);
	
	mlx_hook(game->window, EVENT_KEY_PRESS, 0, key_pressed, game);
	mlx_hook(game->window, EVENT_KEY_RELEASE, 0, key_released, game);
	return (game->data[5].img);
}

void ft_rebdrick(t_game *game, int i, char *path)
{
    if (!(game->data[0].img = mlx_xpm_file_to_image(game->mlx, game->we_p, &(game->data[0].width), &(game->data[0].height))))
	    printf("%p\n%d\n%d\n", game->data[0].img, (game->data[0].width), (game->data[0].height));
    game->data[0].addr = mlx_get_data_addr(game->data[0].img, &(game->data[0].bits_per_pixel), &(game->data[0].line_length), &(game->data[0].endian));
    if (!(game->data[1].img = mlx_xpm_file_to_image(game->mlx, game->we_p, &(game->data[1].width), &(game->data[1].height))))
	    printf("%p\n%d\n%d\n", game->data[1].img, (game->data[1].width), (game->data[1].height));
    game->data[1].addr = mlx_get_data_addr(game->data[1].img, &(game->data[1].bits_per_pixel), &(game->data[1].line_length), &(game->data[1].endian));
    if (!(game->data[2].img = mlx_xpm_file_to_image(game->mlx, game->we_p, &(game->data[2].width), &(game->data[2].height))))
	    printf("%p\n%d\n%d\n", game->data[2].img, (game->data[2].width), (game->data[2].height));
    game->data[2].addr = mlx_get_data_addr(game->data[2].img, &(game->data[2].bits_per_pixel), &(game->data[2].line_length), &(game->data[2].endian));
    if (!(game->data[3].img = mlx_xpm_file_to_image(game->mlx, game->we_p, &(game->data[3].width), &(game->data[3].height))))
	    printf("%p\n%d\n%d\n", game->data[3].img, (game->data[3].width), (game->data[3].height));
    game->data[3].addr = mlx_get_data_addr(game->data[3].img, &(game->data[3].bits_per_pixel), &(game->data[3].line_length), &(game->data[3].endian));
    if (!(game->data[4].img = mlx_xpm_file_to_image(game->mlx, game->we_p, &(game->data[4].width), &(game->data[4].height))))
	    printf("%p\n%d\n%d\n", game->data[4].img, (game->data[4].width), (game->data[4].height));
    game->data[4].addr = mlx_get_data_addr(game->data[4].img, &(game->data[4].bits_per_pixel), &(game->data[4].line_length), &(game->data[4].endian));
}

int	ft_create_window(t_parse *parse, t_game *game)
{
	if (!(game->mlx = mlx_init()))
		write(2, "Error\nMLX init failure", 23);
	game->window = mlx_new_window(game->mlx, parse->x_reso, parse->y_reso, "Nicollage");
	printf("%s\n", game->we_p);
	ft_image(parse, game);
	mlx_loop_hook(game->mlx, ft_loop, game);
	mlx_loop(game->mlx);
	exit(0);
}
