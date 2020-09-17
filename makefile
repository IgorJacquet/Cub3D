CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	cub3d
LIBFT	=	libft/libft.a
MLX	=	minilibx/libmlx.a
MLX_FLGS =	-L minilibx -lmlx -framework OpenGL -framework AppKit

SRC	= 	create_window.c	\
		parse_data.c	\
		parse_map.c	\
		parse_map2.c	\
		parsing.c	\
		raycasting.c

OBJS	= 	$(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MLX) cub3d.h
			$(CC)  $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLGS) -o $(NAME)

$(LIBFT) : 
			make -C libft all

$(MLX) : 
			make -C minilibx all

clean :
			rm -f $(OBJS)
			make -C libft clean

fclean :	clean
			rm -f $(NAME)
			make -C libft fclean

re: fclean all
