/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:09:32 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/12 16:22:45 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_realloc(char **str, char *new, int size, t_parse *parse)
{
	int	i;

	if (!new)
		return (0);
	if (!(parse->map = malloc(sizeof(char *) * (size + 2))))
		return (ft_write_return("Error\nFailed malloc", 0));
	i = -1;
	while (++i < size)
		parse->map[i] = str[i];
	if (!(parse->map[i] = ft_strdup(new)))
		return (ft_write_return("Error\nFailed malloc", 0));
	parse->map[i + 1] = 0;
	if (str)
		free(str);
	return (4219);
}

char	*ft_str_return(char *str)
{
	ft_write_return(str, 0);
	return (NULL);
}

int		his_get_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	ft_freeder(char **new_l, int i)
{
	int r;

	r = 0;
	i += i;
	if (new_l)
	{
		while (new_l[r])
		{
			free(new_l[r]);
			new_l[r++] = NULL;
		}
		free(new_l);
	}
}

int		ft_endprog(t_game *game)
{
	ft_free_exit(game);
	exit(EXIT_SUCCESS);
}
