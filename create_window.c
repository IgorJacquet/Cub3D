/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:14:42 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/09 11:35:21 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		create_trgb(int t, t_parse *parse, int i)
{
	if (i == 0)
		return (t << 24 | parse->ceiling_red << 16 | parse->ceiling_green << 8
		| parse->ceiling_blue);
	else
		return (t << 24 | parse->floor_red << 16 | parse->floor_green << 8
		| parse->floor_blue);
}

int		move_fw(t_game *game, t_parse *parse)
{
	double	space_y;
	double	space_x;
	int		r;

	space_y = (game->dirY >= 0) ? 0.2 : -0.2;
	space_x = (game->dirX >= 0) ? 0.2 : -0.2;
	if (parse->map[(int)(parse->spawn_point[0] - space_y)][(int)(space_x *
		game->forback + parse->spawn_point[1] + (game->dirX * MV_SPD *
		game->forback))] != '1' && parse->map[(int)(parse->spawn_point[0] +
		space_y)][(int)(space_x * game->forback + parse->spawn_point[1] +
		(game->dirX * MV_SPD * game->forback))] != '1')
		parse->spawn_point[1] += game->dirX * game->forback * MV_SPD;
	if (parse->map[(int)(space_y * game->forback + (parse->spawn_point[0] +
		game->dirY * MV_SPD * game->forback))][(int)(parse->spawn_point[1] +
		space_x)] != '1' && parse->map[(int)(space_y * game->forback +
		(parse->spawn_point[0] + game->dirY * MV_SPD * game->forback))]
		[(int)(parse->spawn_point[1] - space_x)] != '1')
		parse->spawn_point[0] += game->dirY * MV_SPD * game->forback;
	r = ft_sprite_dist(game, &game->parse);
	return (r);
}

int		move_lr(t_game *game, t_parse *parse)
{
	double	space_y;
	double	space_x;
	int		r;

	space_y = (game->dirY >= 0) ? 0.2 : -0.2;
	space_x = (game->dirX >= 0) ? 0.2 : -0.2;
	if (parse->map[(int)(parse->spawn_point[0] + space_y)][(int)
		(parse->spawn_point[1] - game->leftright * game->dirY * MV_SPD - space_y
		* game->leftright)] != '1' && parse->map[(int)(parse->spawn_point[0] -
		space_y)][(int)(parse->spawn_point[1] - game->leftright * game->dirY *
		MV_SPD - space_y * game->leftright)] != '1')
		parse->spawn_point[1] -= game->leftright * game->dirY * MV_SPD;
	if (parse->map[(int)(parse->spawn_point[0] + game->leftright * game->dirX *
MV_SPD + space_x * game->leftright)][(int)(parse->spawn_point[1] + space_x)] !=
'1' && parse->map[(int)(parse->spawn_point[0] + game->leftright * game->dirX *
MV_SPD + space_x * game->leftright)][(int)(parse->spawn_point[1] - space_x)])
		parse->spawn_point[0] += game->leftright * game->dirX * MV_SPD;
	r = ft_sprite_dist(game, &game->parse);
	return (r);
}

int		move_turn(t_game *game)
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

int		key_pressed(int key, t_game *game)
{
	if (key == KEY_UP || key == KEY_W)
		game->forback = 1;
	else if (key == KEY_DOWN || key == KEY_S)
		game->forback = -1;
	else if (key == KEY_A)
		game->leftright = -1;
	else if (key == KEY_D)
		game->leftright = 1;
	else if (key == KEY_LEFT)
		game->turn = -1;
	else if (key == KEY_RIGHT)
		game->turn = 1;
	if (key == KEY_ESC)
		ft_free_exit(game);
	return (0);
}

int		key_released(int key, t_game *game)
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
	ft_free_exit(game);
	exit(EXIT_SUCCESS);
}

int		ft_loop(t_game *game)
{
	static int		next = 1;

	if (next)
	{
		ft_raycast(game, (int *)game->data[5].addr, &game->parse);
		mlx_put_image_to_window(game->mlx,
			game->window, game->data[5].img, 0, 0);
		next = 0;
	}
	if (game->forback)
		next = move_fw(game, &game->parse);
	if (game->leftright)
		next = move_lr(game, &game->parse);
	if (game->turn)
		next = move_turn(game);
	return (1);
}

void	*ft_image(t_parse *parse, t_game *game)
{
	game->data[5].img = mlx_new_image(game->mlx, parse->x_reso, parse->y_reso);
	game->data[5].addr = mlx_get_data_addr(game->data[5].img, &game->data[5].
			bits_per_pixel, &game->data[5].line_length, &game->data[5].endian);
	mlx_hook(game->window, EVENT_KEY_PRESS, 0, key_pressed, game);
	mlx_hook(game->window, EVENT_KEY_RELEASE, 0, key_released, game);
	mlx_hook(game->window, 17, 0L, ft_endprog, game);
	return (game->data[5].img);
}

int		ft_text_set(t_game *game, int i, char *path)
{
	int r;

	r = 1;
	if (!(game->data[i].img = mlx_xpm_file_to_image(game->mlx, path,
				&(game->data[i].width), &(game->data[i].height))))
		return (ft_write_return("Error\nWrong texture/sprite path", 0));
	game->data[i].addr = mlx_get_data_addr(game->data[i].img,
				&(game->data[i].bits_per_pixel), &(game->data[i].line_length),
				&(game->data[i].endian));
	if ((game->data[i].height != 64 || game->data[i].width != 64) && i != 4)
		return (ft_write_return("Error\nWrong XPM dimension(s)", 0));
	return (r);
}

int		ft_create_window(t_parse *parse, t_game *game)
{
	if (!(game->mlx = mlx_init()))
		return (ft_write_return("Error\nMLX init failure", 0));
	game->window = mlx_new_window(game->mlx, parse->x_reso, parse->y_reso,
	"Nicollage");
	if (!(game->sp_order = malloc(sizeof(int *) * (parse->sprite_count))))
		return (0);
	if (!((ft_text_set(game, 0, parse->we_p) &&
			(ft_text_set(game, 1, parse->ea_p)) &&
			(ft_text_set(game, 2, parse->no_p)) &&
			(ft_text_set(game, 3, parse->so_p)) &&
			(ft_text_set(game, 4, parse->sprite_text)))))
		return (0);
	ft_sprite_dist(game, parse);
	ft_image(parse, game);
	mlx_loop_hook(game->mlx, ft_loop, game);
	mlx_loop(game->mlx);
	return (0);
}
