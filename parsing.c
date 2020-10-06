/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:51:00 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/06 18:43:01 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_exit(t_game *game)
{
	int i;

	i = -1;
	if (game->mlx)
		mlx_destroy_window(game->mlx, game->window);
	if (game->parse.map)
	{
		printf("free map\n");
		ft_freeder(game->parse.map, 0);
	}
	if (game->parse.sprite)
	{
		printf("free sprite\n");
		free(game->parse.sprite);
	}
	if (game->sp_order)
	{
		printf("free sp_order\n");
		free(game->sp_order);
	}
	if (game->parse.no_p)
	{
		printf("free no_p\n");
		free (game->parse.no_p);
	}
	if (game->parse.so_p)
	{
		printf("free so_p\n");
		free (game->parse.so_p);
	}
	if (game->parse.we_p)
	{
		printf("free we_p\n");
		free (game->parse.we_p);
	}
	if (game->parse.ea_p)
	{
		printf("free ea_p\n");
		free (game->parse.ea_p);
	}
	if (game->parse.sprite_text)
	{
		printf("free sprite_text\n");
		free (game->parse.sprite_text);
	}
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
	if (!(parse->map = malloc(sizeof(char*))))
		return (ft_write_return("Error\nFailed Malloc", 0));
	return (4219);
}

int			ft_freeder(char **new_l, int i)
{
	int r;

	r = 0;
	if (new_l)
	{
		while (new_l[r])
		{
			free(new_l[r]);
			new_l[r++] = NULL;
		}
		free(new_l);
		new_l = NULL;
	}
	return (i);
}

int		ft_checkfile(int argc, char **argv, t_game *game)
{
	char *str;

	game->bmp = 0;
	if (argc != 2 && argc != 3)
		return (ft_write_return("Error\nWrong number of arguments\n", 0));
	str = ft_strrchr(argv[1], '.');
	if (argv[1][0] == '.' && argv[1][1] == 'c' && argv[1][2] == 'u' &&
										argv[1][3] == 'b' && !argv[1][4])
		return (ft_write_return("Error\nWrong file name\n", 0));
	if (str[1] != 'c' || str[2] != 'u' || str[3] != 'b' || str[4])
		return (ft_write_return("Error\nWrong file name\n", 0));
	if (argc == 3)
	{
		if (argv[2][0] != '-' || argv[2][1] != '-' || argv[2][2] != 's' ||
		argv[2][3] != 'a' || argv[2][4] != 'v' || argv[2][5] != 'e' || argv[2][6])
			return (ft_write_return("Error\nWrong arguments\n", 0));
		game->bmp = 1;
	}
	return (4219);
}

void		ft_printdata(t_parse *parse)
{
	int	y;
	int	x;

	y = -1;
	x = 0;
	while (parse->map[++y])
		printf("%s\n", parse->map[y]);
	printf("Resolution X : %d\nResolution Y :%d\nNorth texture path : %s\n South texture Path : %s\nEast texture path : %s\nWest texture path : %s\n Sprite texture path : %s\nFloor red : %d\nFloor green : %d\nFloor blue : %d\n Ceiling red : %d\nCeiling green : %d\nCeiling blue : %d\n", parse->x_reso, parse->y_reso, parse->no_p, parse->so_p, parse->ea_p, parse->we_p, parse->sprite_text, parse->floor_red, parse->floor_green, parse->floor_blue, parse->ceiling_red, parse->ceiling_green, parse->ceiling_blue);
	printf("Spawn Y : %f\nSpawn X : %f\nSpawn orientation : %c\n", parse->spawn_point[0], parse->spawn_point[1], parse->spawn);
}

void	ft_pos_init(t_parse *parse, t_game *game)
{
    game->dirX = 0;
	game->dirY = 0;
	game->planeX = 0;
	game->planeY = 0;
	if (parse->spawn == 'N')
	{
		game->dirY = -1;
		game->planeX = 0.66;
	}
	else if (parse->spawn == 'S')
	{
		game->dirY = 1;
		game->planeX = -0.66;
	}
	else if (parse->spawn == 'E')
    {
		game->dirX = 1;
		game->planeY = 0.66;
	}
	else
    {
		game->dirX = -1;
		game->planeY = -0.66;
	}
}

int			main(int argc, char **argv)
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
	if (!(ft_read_map(fd, &game.parse, line)))
		ft_free_exit(&game);
	ft_pos_init(&game.parse, &game);
	if (game.bmp == 1 && BMPwrite(&game))
		ft_free_exit(&game);
//	ft_printdata(&game.parse);
	if (!(ft_create_window(&game.parse, &game)))
		ft_free_exit(&game);
	return (19);
}
