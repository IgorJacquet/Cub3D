CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address
NAME	=	cub3d
LIBFT	=	libft/libft.a
MLX	=	minilibx/libmlx.a
MLX_FLGS =	-L minilibx -I minilibx -lmlx -framework OpenGL -framework AppKit

SRC	= 	create_window.c	\
		parse_data.c	\
		parse_map.c	\
		parse_data2.c	\
		parsing.c	\
		raycasting.c \
		bmp.c

OBJS	= 	$(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
			$(CC)  $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLGS) -o $(NAME)

$(LIBFT) : 
			make -C libft all

$(MLX) : 
			make -C minilibx all

clean :
			rm -f $(OBJS)
			make -C libft clean
			make -C minilibx clean

fclean :	clean
			rm -f $(NAME)
			make -C libft fclean

re: fclean all
