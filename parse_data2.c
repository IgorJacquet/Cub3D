/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 20:12:03 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/08 14:54:49 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_write_return(char *str, int i)
{
	write(2, str, ft_strlen(str));
	return (i);
}

int		ft_resol_sprite(char **new_l, t_parse *parse)
{
	if (new_l[0] && new_l[0][0] == 'S' && !new_l[0][1])
	{
		if (parse->check[4] == '1')
			return (ft_write_return("Error\nDouble sprite texture", 0));
		if (!(parse->sprite_text = ft_strdup(new_l[1])))
			return (ft_write_return("Error\nFailed Malloc", 0));
		if (new_l[2] || !new_l[1])
			return (ft_write_return("Error\nWrong number of sprite args", 0));
		parse->check[4] = '1';
	}
	else if (new_l[0] && new_l[0][0] == 'R' && !new_l[0][1])
	{
		if (parse->check[7] == '1')
			return (ft_write_return("Error\nDouble resolution\n", 1));
		return (ft_resolution(parse, new_l));
	}
	else if (new_l[0])
		return (-1);
	else
		return (0);
	return (4219);
}

int		ft_parser(char **new_l, t_parse *parse)
{
	int i;

	if ((i = ft_cardinal_y(new_l, parse)) > 0)
		return (i);
	else if ((i = ft_cardinal_x(new_l, parse)) > 0)
		return (i);
	else if ((i = ft_ceiling(new_l, parse, -1)) > 0)
	{
		if (parse->ceiling_green < 0 || parse->ceiling_green > 255 ||
				parse->ceiling_blue < 0 || parse->ceiling_blue > 255 ||
				parse->ceiling_red < 0 || parse->ceiling_red > 255)
			return (ft_write_return("Error\nWrong ceiling RGB", 0));
		return (i);
	}
	else if ((i = ft_floor(new_l, parse, -1)) > 0)
	{
		if (parse->floor_green < 0 || parse->floor_green > 255 ||
				parse->floor_blue < 0 || parse->floor_blue > 255 ||
				parse->floor_red < 0 || parse->floor_red > 255)
			return (ft_write_return("Error\nWrong floor RGB", 0));
		return (i);
	}
	else if ((i = ft_resol_sprite(new_l, parse)) > 0)
		return (i);
	return (i);
}

char	*ft_read_data(int fd, t_parse *parse, char *line)
{
	int		r;
	char	**new_l;

	while ((r = get_next_line(fd, &line)) > 0)
	{
		if (!(new_l = ft_split(line, ' ')))
			exit(write(2, "Error\nFailed malloc\n", 20));
		if (new_l[0] && ft_parser(new_l, parse) != 4219)
		{
			ft_freeder(new_l, 0);
			return (ft_str_return("Error\nInvalid data\n"));
		}
		ft_freeder(new_l, 4219);
		if (ft_strlen(parse->check) == 8)
			break ;
		free(line);
		r = 0;
	}
	if (r == 0)
	{
		ft_write_return("Error\nmissing data", 0);
		return (NULL);
	}
	return (line);
}
