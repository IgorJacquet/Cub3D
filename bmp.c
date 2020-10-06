/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:29:39 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/06 19:11:27 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	int_to_char(unsigned char *str, int value)
{
	str[0] = (unsigned char)(value);
	str[1] = (unsigned char)(value >> 8);
	str[2] = (unsigned char)(value >> 16);
	str[3] = (unsigned char)(value >> 24);
}

static void BMPmake(int filesize, t_game *game, int fd)
{
    unsigned char bitmap[54];
    int i;

	i = 0;
	while (i < 54)
		bitmap[i++] = (unsigned char)(0);
    bitmap[0] = (unsigned char)('B');
    bitmap[1] = (unsigned char)('M');
	int_to_char(bitmap + 2, filesize);
    bitmap[10] = (unsigned char)(54);
    bitmap[14] = (unsigned char)(40);
    int_to_char(bitmap + 18, game->parse.x_reso);
    int_to_char(bitmap + 22, game->parse.y_reso);
    bitmap[26] = (unsigned char)(1);
    bitmap[28] = (unsigned char)(24);
    int_to_char(bitmap + 34, (3 * game->parse.y_reso * game->parse.x_reso));
	write(fd, bitmap, 54);
}

static int	write_data(int fd, t_game *game, int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					x;
	int					y;
	int					color;

	y = 0;
	while (y < game->parse.y_reso)
	{
		x = 0;
		while (x < game->parse.x_reso)
		{
			color = his_get_color(game->data, x, y);
			if (write(fd, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(fd, &zero, pad) < 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int		ft_set_trucs(t_game *game, t_parse *parse)
{
	printf("lol\n");
	if (!(game->mlx = mlx_init()))
		return (ft_write_return("Error\nMLX init failure", 0));
	printf("lol2\n");
	if (!(game->sp_order = malloc(sizeof(int *) * (parse->sprite_count))))
        return(0);
	printf("lol3\n");
	if (!((ft_text_set(game, 0, parse->we_p) && 
			(ft_text_set(game, 1, parse->ea_p)) && 
			(ft_text_set(game, 2, parse->no_p)) && 
			(ft_text_set(game, 3, parse->so_p)) && 
			(ft_text_set(game, 4, parse->sprite_text)))))
		return (0);
	printf("lol4\n");
	ft_sprite_dist(game, parse);
	printf("lol5\n");
	game->data[5].img = mlx_new_image(game->mlx, parse->x_reso, parse->y_reso);
	printf("lol6\n");
	game->data[5].addr = mlx_get_data_addr(game->data[5].img,
		&game->data[5].bits_per_pixel, &game->data[5].line_length, &game->data[5].endian);
	printf("lol7\n");
	ft_raycast(game, (int *)game->data[5].addr, &game->parse);
	printf("lol8\n");
	return (4219);
}

int		BMPwrite(t_game *game)
{
    int fd;
	int padding;
	int filesize;

	padding = (4 - ((int)game->parse.x_reso * 3) % 4) % 4;
	filesize = 54 + (3 * ((int)game->parse.x_reso + padding) * (int)game->parse.y_reso);
    if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU) == -1))
	{
		ft_write_return("Error\nOpen failed", 0);
		ft_free_exit(game);
	}
    BMPmake(filesize, game, fd);
	ft_set_trucs(game, &game->parse);
	while (filesize-- - 54)
		write_data(fd, game, padding);
    close(fd);
	return (4219);
}