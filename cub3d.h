/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:02:30 by ijacquet          #+#    #+#             */
/*   Updated: 2020/09/16 14:55:28 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include "keys.h"

#include <stdio.h>

//# define MV_SPD 0.1

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			width;
	int			height;
}               t_data;

typedef	struct	s_parse
{
	int		x_reso;
    int		y_reso;
	char	*no_p;
	char	*so_p;
	char	*we_p;
	char	*ea_p;
	char	*sprite_text;
	int		floor_red;
	int		floor_green;
	int		floor_blue;
	int		ceiling_red;
	int		ceiling_green;
	int		ceiling_blue;
	char	check[8];
	char	*ret;
	char	**map;
	char	spawn;
	double		spawn_point[2];
}				t_parse;

typedef struct s_game
{
	void *mlx;
	void *window;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
    int    mapX;
    int    mapY;
    double cameraX;
    double rayDirX;
    double rayDirY;
    double sideDistX;
    double sideDistY;
	double deltaDistX;
    double deltaDistY;
    double perpWallDist;
	int lineHeight;
	int forback;
	int leftright;
	int x_reso;
	int y_reso;
	double spawn_point[2];
	char spawn;
	char **map;
	int ceiling_red;
	int ceiling_green;
    int ceiling_blue;
	int floor_red;
	int floor_green;
    int floor_blue;
	int turn;
	int side;
	int stepX;
	int stepY;
	t_data data[6];
	char	*no_p;
	char	*so_p;
	char	*we_p;
	char	*ea_p;
	char	*sprite_text;
}				t_game;

int		ft_create_window(t_parse *parse, t_game *game);
char	*ft_read_map(int fd, t_parse *parse, char *line);
char	*ft_read_data(int fd, t_parse *parse, char *line);
int		ft_parser(char **new_l, t_parse *parse);
int		ft_resol_sprite(char **new_l, t_parse *parse);
int		ft_ceiling(char **new_l, t_parse *parse, int i);
int		ft_floor(char **new_l, t_parse *parse, int i);
int		ft_cardinal_x(char **new_l, t_parse *parse);
int		ft_cardinal_y(char **new_l, t_parse *parse);
int		create_trgb(int t, t_game *game, int i);
int		ft_resolution(t_parse *parse, char **str);
int		ft_freeder(char **new_l, int r);
void	ft_printdata(t_parse *parse);
int		ft_struct_set(t_parse *parse, t_game *game);
int		ft_checkfile(int argc, char **argv);
int		*ft_raycast(t_game *game, int *img_ptr);
int		mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
void	ft_parse_to_game(t_parse *parse, t_game *game);

#endif
