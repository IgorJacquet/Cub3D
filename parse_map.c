/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 20:07:07 by ijacquet          #+#    #+#             */
/*   Updated: 2020/09/25 12:25:07 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_realloc(char **str, char *new, int size, t_parse *parse)
{
	int	i;

	if (!new)
		return (0);
	if (!(parse->map = malloc(sizeof(char *) * (size + 2))))
		return (0);
	i = -1;
	while (++i < size)
		parse->map[i] = str[i];
	parse->map[i] = ft_strdup(new);
	parse->map[i + 1] = 0;
	if (str)
		free(str);
	return (4219);
}

void		ft_sprite_data(t_parse *parse)
{
	int x;
	int y;
	int i;

	i = 0;
	y = 0;
	while (parse->map[++y])
	{
		x = 0;
		while (parse->map[y][++x])
			if (parse->map[y][x] == '2')
			{
				parse->sprite[i].x = x + 0.5;
				parse->sprite[i].y = y + 0.5;
				i++;
			}
	}
}

static int	ft_valid(int y, int x, t_parse *parse)
{
	if (parse->map[y][x] != 32 && parse->map[y][x] != 48 && \
		parse->map[y][x] != 49 && parse->map[y][x] != 50 && \
		parse->map[y][x] != 69 && parse->map[y][x] != 78 && \
		parse->map[y][x] != 87 && parse->map[y][x] != 83)
		exit(write(2, "Error\nInvalid map", 17));
	if (x == 0)
	{
		if (parse->map[y][x] != '1' && parse->map[y][x] != ' ')
			exit(write(2, "Error\nInvalid map", 17));
	}
	else if (parse->map[y][x] == '0' || parse->map[y][x] == 'N' || \
			parse->map[y][x] == 'S' || parse->map[y][x] == 'E' || \
			parse->map[y][x] == 'W' || parse->map[y][x] == '2')
	{
		if ((x + 1) > (int)ft_strlen(parse->map[y - 1]) || \
			(x + 1) > (int)ft_strlen(parse->map[y + 1]))
			exit(write(2, "Error\nInvalid map", 17));
		else if (parse->map[y][x - 1] == ' ' || parse->map[y][x + 1] == ' ' ||
					parse->map[y - 1][x] == 32 || parse->map[y + 1][x] == 32 ||
					parse->map[y][x + 1] == 0)
			exit(write(2, "Error\nInvalid map", 17));
	}
	return (4219);
}

static int	ft_map_parser(t_parse *parse, int size, int x, int y)
{
	while (parse->map[0][++x])
		if (parse->map[0][x] != '1' && parse->map[0][x] != ' ')
			exit(write(2, "Error\nInvalid map", 17));
	x = 0;
	while (y < size - 1 && parse->map[++y][x])
	{
		while (parse->map[y][x])
		{
			if (parse->map[y][x] == 'N' || parse->map[y][x] == 'S' || \
				parse->map[y][x] == 'E' || parse->map[y][x] == 'W')
			{
				if (parse->spawn != 0)
					exit(write(2, "Error\nMultiple spawns\n", 22));
				parse->spawn = parse->map[y][x];
				parse->spawn_point[0] = y + 0.5;
				parse->spawn_point[1] = x + 0.5;
			}
			if (parse->map[y][x] == '2')
				parse->sprite_count++;
			ft_valid(y, x++, parse);
		}
		x = 0;
	}
	if (!(parse->sprite = malloc(sizeof(t_sprite) * parse->sprite_count)))
		return (0);
	ft_sprite_data(parse);
	while (parse->map[size][++x])
		if (parse->map[size][x] != '1' && parse->map[size][x] != ' ')
			exit(write(2, "Error\nInvalid map", 17));
	return (4219);
}

char		*ft_read_map(int fd, t_parse *parse, char *line)
{
	int		r;
	int		size;

	size = -1;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		if ((line[0] != 0) || size > -1)
			ft_realloc(parse->map, line, ++size, parse);
		if (size != 0 && line[0] != 0 && parse->map[size - 1][0] == 0)
			exit(write(2, "Error\nInvalid map", 17));
		free(line);
	}
	if (r == 0)
	{
		ft_realloc(parse->map, line, size + 1, parse);
		free(line);
	}
	if (!parse->map[0][0])
		exit(write(2, "Error\nNo map", 12));
	ft_map_parser(parse, size + 1, -1, 0);
	if (parse->spawn == 0)
		exit(write(2, "Error\nNo spawn", 14));
	return (line);
}
