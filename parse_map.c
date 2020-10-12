/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 20:07:07 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/12 16:20:26 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_valid(int y, int x, t_parse *parse)
{
	if (parse->map[y][x] != 32 && parse->map[y][x] != 48 &&
		parse->map[y][x] != 49 && parse->map[y][x] != 50 &&
		parse->map[y][x] != 69 && parse->map[y][x] != 78 &&
		parse->map[y][x] != 87 && parse->map[y][x] != 83)
		return (ft_write_return("Error\nInvalid map", 0));
	if (x == 0)
	{
		if (parse->map[y][x] != '1' && parse->map[y][x] != ' ')
			return (ft_write_return("Error\nInvalid map", 0));
	}
	else if (parse->map[y][x] == '0' || parse->map[y][x] == 'N' ||
			parse->map[y][x] == 'S' || parse->map[y][x] == 'E' ||
			parse->map[y][x] == 'W' || parse->map[y][x] == '2')
	{
		if ((x + 1) > (int)ft_strlen(parse->map[y - 1]) || \
			(x + 1) > (int)ft_strlen(parse->map[y + 1]))
			return (ft_write_return("Error\nInvalid map", 0));
		else if (parse->map[y][x - 1] == ' ' || parse->map[y][x + 1] == ' ' ||
					parse->map[y - 1][x] == 32 || parse->map[y + 1][x] == 32 ||
					parse->map[y][x + 1] == 0)
			return (ft_write_return("Error\nInvalid map", 0));
	}
	return (4219);
}

static int	ft_last_line_check(t_parse *parse, int x, int y)
{
	if (!(parse->sprite = malloc(sizeof(t_sprite) * parse->sprite_count)))
		return (ft_write_return("Error\nFailed malloc", 0));
	while (parse->map[y][x])
	{
		if (parse->map[y][x] != '1' && parse->map[y][x] != ' ')
			return (ft_write_return("Error\nInvalid map", 0));
		x++;
	}
	ft_sprite_data(parse);
	return (4219);
}

static int	ft_map_parser(t_parse *parse, int size, int x, int y)
{
	while (parse->map[0][++x])
		if (parse->map[0][x] != '1' && parse->map[0][x] != ' ')
			return (ft_write_return("Error\nInvalid map", 0));
	x = 0;
	while (parse->map[++y][x] && y < size - 1)
	{
		while (parse->map[y][x])
		{
			if (parse->map[y][x] == 'N' || parse->map[y][x] == 'S' || \
				parse->map[y][x] == 'E' || parse->map[y][x] == 'W')
			{
				if (parse->spawn != 0)
					return (ft_write_return("Error\nMultiple spawns\n", 0));
				parse->spawn = parse->map[y][x];
				parse->spawn_point[0] = y + 0.5;
				parse->spawn_point[1] = x + 0.5;
			}
			if (parse->map[y][x] == '2')
				parse->sprite_count++;
			if (!(ft_valid(y, x++, parse)))
				return (0);
		}
		x = 0;
	}
	return (ft_last_line_check(parse, x, y));
}

char		*ft_map_gnl_check(t_parse *parse, int size, int r)
{
	if (r < 0)
		return (ft_str_return("Error\nGet next line failed"));
	if (!parse->map[0][0])
		return (ft_str_return("Error\nNo map"));
	if (!(ft_map_parser(parse, size + 1, -1, 0)))
		return (NULL);
	if (parse->spawn == 0)
		return (ft_str_return("Error\nNo spawn"));
	return ("ok");
}

char		*ft_read_map(int fd, t_parse *parse, char *line, int count)
{
	int		r;
	int		size;

	size = -1;
	while ((r = get_next_line(fd, &line)) >= 0)
	{
		if (count == 1 && !line[0])
			count = 2;
		if (line[0])
		{
			if (!(ft_realloc(parse->map, line, ++size, parse)))
				return (NULL);
			if (count == 2 && line[0])
				return (ft_str_return("Error\nInvalid map"));
			if (count == 0)
				count = 1;
		}
		if (size != 0 && line[0] != 0 && parse->map[size - 1][0] == 0)
			return (ft_str_return("Error\nInvalid map"));
		free(line);
		if (r == 0)
			break ;
	}
	return (ft_map_gnl_check(parse, size, r));
}
