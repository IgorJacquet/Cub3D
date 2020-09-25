/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:51:00 by ijacquet          #+#    #+#             */
/*   Updated: 2020/09/25 16:56:53 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		exit(write(2, "Error\nFailed Malloc\n", 20));
	return (4219);
}

int			ft_freeder(char **new_l, int r)
{
	while (new_l[r])
		free(new_l[r++]);
	free(new_l);
	return (4219);
}

int		ft_checkfile(int argc, char **argv)
{
	char *str;

	if (argc != 2)
		return (write(2, "Error\nWrong number of arguments\n", 32));
	str = ft_strrchr(argv[1], '.');
	if (argv[1][0] == '.')
		return (write(2, "Error\nWrong file name\n", 22));
	if (str[1] != 'c' || str[2] != 'u' || str[3] != 'b' || str[4])
		return (write(2, "Error\nWrong file name\n", 22));
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

void	ft_parse_to_game(t_parse *parse, t_game *game)
{
	int i;

	i = -1;
	game->x_reso = parse->x_reso;
	game->y_reso = parse->y_reso;
	game->spawn_point[0] = parse->spawn_point[0];
	game->spawn_point[1] = parse->spawn_point[1];
	game->spawn = parse->spawn;
	game->map = parse->map;
	game->ceiling_red = parse->ceiling_red;
	game->ceiling_green = parse->ceiling_green;
    game->ceiling_blue = parse->ceiling_blue;
	game->floor_red = parse->floor_red;
	game->floor_green = parse->floor_green;
    game->floor_blue = parse->floor_blue;
	game->so_p = parse->so_p;
	game->no_p = parse->no_p;
	game->we_p = parse->we_p;
	game->ea_p = parse->ea_p;
	game->sprite_text = parse->sprite_text;
    if (game->spawn == 'N')
        game->dirX = 0, game->dirY = -1, game->planeX = 0.66, game->planeY = 0;
    else if (game->spawn == 'S')
        game->dirX = 0, game->dirY = 1, game->planeX = -0.66, game->planeY = 0;
    else if (game->spawn == 'E')
        game->dirX = 1, game->dirY = 0, game->planeX = 0, game->planeY = 0.66;
    else
        game->dirX = -1, game->dirY = 0, game->planeX = 0, game->planeY = -0.66;
	game->sprite = parse->sprite;
	game->sprite_count = parse->sprite_count;
}
// ATTENTION_PARSING_RGB_TRASH_ET_PROBLEME_NBRS_ARGUMENTS
int			main(int argc, char **argv)
{
	int		fd;
	t_parse	parse;
	t_game	game;
	char	*line;

	line = NULL;
	if (ft_checkfile(argc, argv) != 4219)
		return (19);
	fd = open(argv[1], O_RDONLY);
	if (ft_struct_set(&parse, &game) != 4219)
		return (19);
	line = ft_read_data(fd, &parse, line);
	line = ft_read_map(fd, &parse, line);
	ft_parse_to_game(&parse, &game);
//	ft_printdata(&parse);
	ft_create_window(&parse, &game);
	return (19);
}
