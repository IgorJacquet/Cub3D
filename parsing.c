/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:51:00 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/12 16:25:18 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_exit(t_game *game)
{
	int i;

	i = -1;
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->parse.map)
		ft_freeder(game->parse.map, 0);
	if (game->parse.sprite)
		free(game->parse.sprite);
	if (game->sp_order)
		free(game->sp_order);
	if (game->parse.no_p)
		free(game->parse.no_p);
	if (game->parse.so_p)
		free(game->parse.so_p);
	if (game->parse.we_p)
		free(game->parse.we_p);
	if (game->parse.ea_p)
		free(game->parse.ea_p);
	if (game->parse.sprite_text)
		free(game->parse.sprite_text);
	exit(EXIT_SUCCESS);
}

int		ft_struct_set(t_parse *parse, t_game *game)
{
	parse->spawn = 0;
	parse->x_reso = 0;
	parse->y_reso = 0;
	parse->ceiling_blue = -1;
	parse->ceiling_green = -1;
	parse->spawn = 0;
	game->forback = 0;
	game->leftright = 0;
	game->turn = 0;
	parse->sprite_count = 0;
	parse->map = NULL;
	parse->sprite = 0;
	game->sp_order = 0;
	parse->no_p = 0;
	parse->so_p = 0;
	parse->we_p = 0;
	parse->ea_p = 0;
	parse->sprite_text = 0;
	return (4219);
}

int		ft_checkfile(int argc, char **argv, t_game *game)
{
	char *str;

	game->bmp = 0;
	if (argc != 2 && argc != 3)
		return (ft_write_return("Error\nWrong number of arguments\n", 0));
	if (!(str = ft_strrchr(argv[1], '.')))
		return (ft_write_return("Error\nWrong file name\n", 0));
	if (argv[1][0] == '.' && argv[1][1] == 'c' && argv[1][2] == 'u' &&
										argv[1][3] == 'b' && !argv[1][4])
		return (ft_write_return("Error\nWrong file name\n", 0));
	if (str[1] != 'c' || str[2] != 'u' || str[3] != 'b' || str[4])
		return (ft_write_return("Error\nWrong file name\n", 0));
	if (argc == 3)
	{
		if (argv[2][0] != '-' || argv[2][1] != '-' || argv[2][2] != 's' ||
		argv[2][3] != 'a' || argv[2][4] != 'v'
		|| argv[2][5] != 'e' || argv[2][6])
			return (ft_write_return("Error\nWrong arguments\n", 0));
		game->bmp = 1;
	}
	return (4219);
}

void	ft_pos_init(t_parse *parse, t_game *game)
{
	game->dirx = 0;
	game->diry = 0;
	game->planex = 0;
	game->planey = 0;
	if (parse->spawn == 'N')
	{
		game->diry = -1;
		game->planex = 0.66;
	}
	else if (parse->spawn == 'S')
	{
		game->diry = 1;
		game->planex = -0.66;
	}
	else if (parse->spawn == 'E')
	{
		game->dirx = 1;
		game->planey = 0.66;
	}
	else
	{
		game->dirx = -1;
		game->planey = -0.66;
	}
}

int		main(int argc, char **argv)
{
	int		fd;
	t_game	game;
	char	*line;

	line = NULL;
	if (ft_checkfile(argc, argv, &game) != 4219)
		return (21);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_write_return("Error\nOpen file failed", 21));
	if (ft_struct_set(&game.parse, &game) != 4219)
		ft_free_exit(&game);
	if (!(line = ft_read_data(fd, &game.parse, line)))
		ft_free_exit(&game);
	if (!(ft_read_map(fd, &game.parse, line, 0)))
		ft_free_exit(&game);
	ft_pos_init(&game.parse, &game);
	if (game.bmp == 1 && bmp_write(&game))
		ft_free_exit(&game);
	if (!(ft_create_window(&game.parse, &game)))
		ft_free_exit(&game);
	return (19);
}
