/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 20:08:56 by ijacquet          #+#    #+#             */
/*   Updated: 2020/09/11 14:24:55 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_resolution(t_parse *parse, char **str)
{
	int i;

	i = 0;
	if (str[3] || !str[1] || !str[2])
		exit(write(2, "Error\nwrong number of resolution arguments\n", 43));
	if (ft_atoi(str[1]) < 0 || ft_atoi(str[2]) < 0)
		exit(write(2, "Error\nWrong resolution\n", 23));
	parse->x_reso = ft_atoi(str[1]);
	parse->y_reso = ft_atoi(str[2]);
	while (str[1][i++])
		if (str[1][i] < '0' && str[1][i] > '9')
			exit(write(2, "Error\nWrong resolution\n", 23));
	i = 0;
	while (str[2][i++])
		if (str[2][i] < '0' && str[2][i] > '9')
			exit(write(2, "Error\nWrong resolution\n", 23));
	if (parse->x_reso > 5120)
		parse->x_reso = 5120;
	if (parse->y_reso > 2880)
		parse->y_reso = 2880;
	if (!parse->x_reso || !parse->y_reso || parse->x_reso < 0 ||
											parse->y_reso < 0)
		exit(write(2, "Error\nWrong resolution\n", 23));
	parse->check[7] = '1';
	return (4219);
}

int	ft_cardinal_y(char **new_l, t_parse *parse)
{
	if (new_l[0] && new_l[0][0] == 'N' && new_l[0][1] == 'O' && !new_l[0][2])
	{
		if (parse->check[0] == '1')
			exit(write(2, "Error\nDouble North texture\n", 27));
		if (new_l[2] || !new_l[1])
			exit(write(2, "Error\nWrong number of north arguments\n", 38));
		if (!(parse->no_p = ft_strdup(new_l[1])))
			exit(write(2, "Error\nFailed Malloc\n", 20));
		parse->check[0] = '1';
	}
	if (new_l[0] && new_l[0][0] == 'S' && new_l[0][1] == 'O' && !new_l[0][2])
	{
		if (parse->check[1] == '1')
			exit(write(2, "Error\nDouble South texture\n", 27));
		if (new_l[2] || !new_l[1])
			exit(write(2, "Error\nWrong number of south arguments\n", 38));
		if (!(parse->so_p = ft_strdup(new_l[1])))
			exit(write(2, "Error\nFailed Malloc\n", 20));
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
			exit(write(2, "Error\nDouble East texture\n", 26));
		if (new_l[2] || !new_l[1])
			return (ft_printf("Error\nWrong number of east arguments"));
		if (!(parse->ea_p = ft_strdup(new_l[1])))
			return (ft_printf("Error\nFailed Malloc"));
		parse->check[2] = '1';
	}
	else if (new_l[0] && new_l[0][0] == 'W' &&
			new_l[0][1] == 'E' && !new_l[0][2])
	{
		if (parse->check[3] == '1')
			return (ft_printf("Error\nDouble West texture"));
		if (new_l[2] || !new_l[1])
			return (ft_printf("Error\nWrong number of west arguments"));
		if (!(parse->we_p = ft_strdup(new_l[1])))
			return (ft_printf("Error\nFailed Malloc"));
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
			return (ft_printf("Error\nDouble floor color"));
		if (!new_l[1])
			return (ft_printf("Error\nWrong number of floor arguments"));
		parse->floor_red = ft_atoi(new_l[1]);
		while (*new_l[1]++ != ',' && i++)
			if (!*new_l[1] || (*new_l[1] < '0' && *new_l[1] > '9'))
				return (write(2, "Error\nWrong floor RGB", 21));
		parse->floor_green = ft_atoi(new_l[1]);
		while (*new_l[1]++ != ',' && i++)
			if (!*new_l[1] || (*new_l[1] < '0' && *new_l[1] > '9'))
				return (write(2, "Error\nWrong floor RGB", 21));
		parse->floor_blue = ft_atoi(new_l[1]);
		while (*new_l[1]++ && i++)
			if ((*new_l[1] < '0' && *new_l[1] > '9') || new_l[2])
				return (write(2, "Error\nWrong floor RGB", 21));
		new_l[1] = new_l[1] - i - 2;
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
			return (ft_printf("Error\nDouble ceiling color"));
		if (!new_l[1])
			return (ft_printf("Error\nWrong number of ceiling arguments"));
		parse->ceiling_red = ft_atoi(new_l[1]);
		while (*new_l[1] && *new_l[1]++ != ',' && i++)
			if (!*new_l[1] || (*new_l[1] < '0' && *new_l[1] > '9'))
				return (write(2, "Error\nWrong ceiling RGB", 23));
		parse->ceiling_green = ft_atoi(new_l[1]);
		while (*new_l[1]++ != ',' && i++)
			if (!*new_l[1] || (*new_l[1] < '0' && *new_l[1] > '9'))
				return (write(2, "Error\nWrong ceiling RGB", 23));
		parse->ceiling_blue = ft_atoi(new_l[1]);
		while (*new_l[1]++ && i++)
			if ((*new_l[1] < '0' && *new_l[1] > '9') || new_l[2])
				return (write(2, "Error\nWrong ceiling RGB", 23));
		new_l[1] = new_l[1] - i - 2;
		parse->check[6] = '1';
	}
	else
		return (0);
	return (4219);
}
