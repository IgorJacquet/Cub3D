/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 20:08:56 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/01 12:19:42 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_resolution(t_parse *parse, char **str)
{
	int i;

	i = 0;
	if (str[3] || !str[1] || !str[2])
		return (ft_write_return("Error\nwrong number of res arguments\n", 0));
	if (ft_atoi(str[1]) < 0 || ft_atoi(str[2]) < 0)
		return (ft_write_return("Error\nWrong resolution\n", 0));
	parse->x_reso = ft_atoi(str[1]);
	parse->y_reso = ft_atoi(str[2]);
	while (str[1][i++])
		if (str[1][i] < '0' && str[1][i] > '9')
			return (ft_write_return("Error\nWrong resolution\n", 0));
	i = 0;
	while (str[2][i++])
		if (str[2][i] < '0' && str[2][i] > '9')
			return (ft_write_return("Error\nWrong resolution\n", 0));
	if (parse->x_reso > 2560)
		parse->x_reso = 2560;
	if (parse->y_reso > 1440)
		parse->y_reso = 1440;
	if (!parse->x_reso || !parse->y_reso || parse->x_reso < 0 ||
											parse->y_reso < 0)
		return (ft_write_return("Error\nWrong resolution\n", 0));
	parse->check[7] = '1';
	return (4219);
}

int	ft_cardinal_y(char **new_l, t_parse *parse)
{
	if (new_l[0] && new_l[0][0] == 'N' && new_l[0][1] == 'O' && !new_l[0][2])
	{
		if (parse->check[0] == '1')
			return (ft_write_return("Error\nDouble North texture\n", 0));
		if (new_l[2] || !new_l[1])
			return (ft_write_return("Error\nWrong number of north arguments\n", 0));
		if (!(parse->no_p = ft_strdup(new_l[1])))
			return (ft_write_return("Error\nFailed Malloc\n", 0));
		parse->check[0] = '1';
	}
	else if (new_l[0] && new_l[0][0] == 'S' && new_l[0][1] == 'O' && !new_l[0][2])
	{
		if (parse->check[1] == '1')
			return (ft_write_return("Error\nDouble South texture\n", 0));
		if (new_l[2] || !new_l[1])
			return (ft_write_return("Error\nWrong number of south arguments\n", 0));
		if (!(parse->so_p = ft_strdup(new_l[1])))
			return (ft_write_return("Error\nFailed Malloc\n", 0));
		parse->check[1] = '1';
	}
	else
		return (0);
	return (4219);
}

int	ft_cardinal_x(char **new_l, t_parse *parse)
{
	if (new_l[0] && new_l[0][0] == 'E' && new_l[0][1] == 'A' && !new_l[0][2])
	{
		if (parse->check[2] == '1')
			return (ft_write_return("Error\nDouble East texture\n", 0));
		if (new_l[2] || !new_l[1])
			return (ft_write_return("Error\nWrong number of east arguments", 0));
		if (!(parse->ea_p = ft_strdup(new_l[1])))
			return (ft_write_return("Error\nFailed Malloc", 0));
		parse->check[2] = '1';
	}
	else if (new_l[0] && new_l[0][0] == 'W' &&
			new_l[0][1] == 'E' && !new_l[0][2])
	{
		if (parse->check[3] == '1')
			return (ft_write_return("Error\nDouble West texture", 0));
		if (new_l[2] || !new_l[1])
			return (ft_write_return("Error\nWrong number of west arguments", 0));
		if (!(parse->we_p = ft_strdup(new_l[1])))
			return (ft_write_return("Error\nFailed Malloc", 0));
		parse->check[3] = '1';
	}
	else
		return (0);
	return (4219);
}

int	ft_floor(char **new_l, t_parse *parse, int i)
{
	if (new_l[0] && new_l[0][0] == 'F' && !new_l[0][1])
	{
		if (parse->check[5] == '1')
			return (ft_write_return("Error\nDouble floor color", 0));
		if (!new_l[1])
			return (ft_write_return("Error\nWrong number of floor arguments", 0));
		parse->floor_red = ft_atoi(new_l[1]);
		while (new_l[1][++i] != ',')
			if (!new_l[1][i] || (new_l[1][i] < '0' || new_l[1][i] > '9'))
				return (ft_write_return("Error\nWrong floor RGB", 0));
		parse->floor_green = ft_atoi(new_l[1] + i + 1);
		while (new_l[1][++i] != ',')
			if (!new_l[1][i] || (new_l[1][i] < '0' || new_l[1][i] > '9'))
				return (ft_write_return("Error\nWrong floor RGB", 0));
		parse->floor_blue = ft_atoi(new_l[1] + i + 1);
		while (new_l[1][++i])
			if ((new_l[1][i] < '0' || new_l[1][i] > '9') || new_l[2])
				return (ft_write_return("Error\nWrong floor RGB", 0));
		parse->check[5] = '1';
	}
	else
		return (0);
	return (4219);
}

int	ft_ceiling(char **new_l, t_parse *parse, int i)
{
	if (new_l[0] && new_l[0][0] == 'C' && !new_l[0][1])
	{
		if (parse->check[6] == '1')
			return (ft_write_return("Error\nDouble ceiling color", 0));
		if (!new_l[1])
			return (ft_write_return("Error\nWrong number of ceiling arguments", 0));
		parse->ceiling_red = ft_atoi(new_l[1]);
		while (new_l[1][++i] != ',')
			if (!new_l[1][i] || (new_l[1][i] < '0' && new_l[1][i] > '9'))
				return (ft_write_return("Error\nWrong ceiling RGB", 0));
		parse->ceiling_green = ft_atoi(new_l[1] + i + 1);
		while (new_l[1][++i] != ',')
			if (!new_l[1][i] || (new_l[1][i] < '0' && new_l[1][i] > '9'))
				return (ft_write_return("Error\nWrong ceiling RGB", 0));
		parse->ceiling_blue = ft_atoi(new_l[1] + i + 1);
		while (new_l[1][++i])
			if ((new_l[1][i] < '0' && new_l[1][i] > '9') || new_l[2])
				return (ft_write_return("Error\nWrong ceiling RGB", 0));
		parse->check[6] = '1';
	}
	else
		return (0);
	return (4219);
}
