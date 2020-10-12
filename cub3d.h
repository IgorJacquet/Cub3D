/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:02:30 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/12 16:33:40 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include "keys.h"

# define MV_SPD 0.05

typedef struct	s_screen
{
	int			drawstart;
	int			drawend;
	int			texx;
	double		step;
	double		texpos;
}				t_screen;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_data;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
}				t_sprite;

typedef struct	s_spr_data
{
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			sp_height;
	int			drawstarty;
	int			drawendy;
	int			spritewidth;
	int			drawstartx;
	int			drawendx;
	int			texx;
	int			texy;
}				t_sp_data;

typedef	struct	s_parse
{
	int			x_reso;
	int			y_reso;
	char		*no_p;
	char		*so_p;
	char		*we_p;
	char		*ea_p;
	char		*sprite_text;
	int			floor_red;
	int			floor_green;
	int			floor_blue;
	int			ceiling_red;
	int			ceiling_green;
	int			ceiling_blue;
	char		check[8];
	char		*ret;
	char		**map;
	char		spawn;
	double		spawn_point[2];
	t_sprite	*sprite;
	int			sprite_count;
}				t_parse;

typedef struct	s_game
{
	void		*mlx;
	void		*window;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	int			mapx;
	int			mapy;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			lineheight;
	int			forback;
	int			leftright;
	int			turn;
	int			side;
	int			stepx;
	int			stepy;
	t_data		data[6];
	char		*sprite_text;
	int			sprite_count;
	int			*sp_order;
	t_parse		parse;
	int			bmp;
	t_sp_data	sp;
	t_screen	screen;
}				t_game;

int				ft_create_window(t_parse *parse, t_game *game);
char			*ft_read_map(int fd, t_parse *parse, char *line, int count);
char			*ft_read_data(int fd, t_parse *parse, char *line);
int				ft_parser(char **new_l, t_parse *parse);
int				ft_resol_sprite(char **new_l, t_parse *parse);
int				ft_ceiling(char **new_l, t_parse *parse, int i);
int				ft_floor(char **new_l, t_parse *parse, int i);
int				ft_cardinal_x(char **new_l, t_parse *parse);
int				ft_cardinal_y(char **new_l, t_parse *parse);
int				create_trgb(int t, t_parse *parse, int i);
int				ft_resolution(t_parse *parse, char **str);
void			ft_freeder(char **new_l, int i);
void			ft_printdata(t_parse *parse);
int				ft_struct_set(t_parse *parse, t_game *game);
int				ft_checkfile(int argc, char **argv, t_game *game);
int				*ft_raycast(t_game *game, int *img_ptr, t_parse *parse);
int				mlx_hook(void *win_ptr, int x_event, int x_mask,
				int (*funct)(), void *param);
void			ft_parse_to_game(t_parse *parse, t_game *game);
int				ft_sprite_dist(t_game *game, t_parse *parse);
int				ft_write_return(char *str, int i);
void			ft_free_exit(t_game *game);
int				his_get_color(t_data *data, int x, int y);
int				bmp_write(t_game *game);
int				ft_text_set(t_game *game, int i, char *path);
int				ft_loop(t_game *game);
char			*ft_str_return(char *str);
void			ft_sprite_draw(t_game *game, t_parse *parse,
				double zbuffer[parse->x_reso], int *img_ptr);
int				move_fw(t_game *game, t_parse *parse);
int				move_lr(t_game *game, t_parse *parse);
int				move_turn(t_game *game);
int				ft_key_pressed(int key, t_game *game);
int				ft_key_released(int key, t_game *game);
int				ft_endprog(t_game *game);
int				ft_realloc(char **str, char *new, int size, t_parse *parse);
void			ft_sprite_data(t_parse *parse);
void			ft_draw_screen(t_game *game, int *img_ptr, int x,
				t_parse *parse);

#endif
