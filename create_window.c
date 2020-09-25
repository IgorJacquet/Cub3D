/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:14:42 by ijacquet          #+#    #+#             */
/*   Updated: 2020/09/25 17:49:07 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double MV_SPD = 0.01;

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
	int r;

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
    r = ft_sprite_dist(game);
	return (r);
}

int			move_lr(t_game *game)
{
	double space_Y;
	double space_X;
	int r;

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
    r = ft_sprite_dist(game);
	return (r);
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

int		ft_endprog(t_game *game)
{
	(void)game;
	exit(EXIT_SUCCESS);
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
	mlx_hook(game->window, 17, 0L, ft_endprog, game);
	return (game->data[5].img);
}

int ft_rebdrick(t_game *game, int i, char *path)
{
	int r;

	r = 1;
    if (!(game->data[i].img = mlx_xpm_file_to_image(game->mlx, path, &(game->data[i].width), &(game->data[i].height))))
	    r = printf("%p\n%d\n%d\nabruti\n", game->data[i].img, (game->data[i].width), (game->data[i].height));
    game->data[i].addr = mlx_get_data_addr(game->data[i].img, &(game->data[i].bits_per_pixel), &(game->data[i].line_length), &(game->data[i].endian));
	return (r);
}

int	ft_create_window(t_parse *parse, t_game *game)
{
	int r;

	if (!(game->mlx = mlx_init()))
		write(2, "Error\nMLX init failure", 23);
	game->window = mlx_new_window(game->mlx, parse->x_reso, parse->y_reso, "Nicollage");
	r = ft_rebdrick(game, 0, game->we_p);
	r = ft_rebdrick(game, 1, game->ea_p);
	r = ft_rebdrick(game, 2, game->no_p);
	r = ft_rebdrick(game, 3, game->so_p);
	r = ft_rebdrick(game, 4, game->sprite_text);
    r = ft_sprite_dist(game);
	ft_image(parse, game);
	mlx_loop_hook(game->mlx, ft_loop, game);

	mlx_loop(game->mlx);
	return(0);
}
