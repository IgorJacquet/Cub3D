# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 16:16:03 by ijacquet          #+#    #+#              #
#    Updated: 2020/09/28 17:25:36 by ijacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CCFLAGS		=	-Wall -Wextra -Werror

NAME		=	libft.a

SRC			= 	ft_atoi.c	ft_bzero.c	ft_calloc.c	ft_isalnum.c	ft_isalpha.c	\
				ft_isascii.c	ft_isdigit.c	ft_isprint.c	ft_itoa.c			\
				ft_memccpy.c	ft_memchr.c	ft_memcmp.c	ft_memcpy.c	ft_memmove.c	\
				ft_memset.c	ft_putchar_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c			\
				ft_putstr_fd.c	ft_split.c	ft_strcat.c	ft_strchr.c	ft_strcpy.c		\
				ft_strdup.c	ft_strjoin.c	ft_strlcat.c	ft_strlcpy.c			\
				ft_strlen.c	ft_strmapi.c	ft_strncmp.c	ft_strndup.c			\
				ft_strnstr.c	ft_strrchr.c	ft_strtrim.c	ft_substr.c			\
				ft_tolower.c	ft_toupper.c	ft_lstadd_back_bonus.c				\
				ft_lstadd_front_bonus.c	ft_lstclear_bonus.c	ft_lstdelone_bonus.c	\
				ft_lstiter_bonus.c	ft_lstlast_bonus.c	ft_lstnew_bonus.c			\
				ft_lstsize_bonus.c	get_next_line.c	ft_memcat.c	ft_freeturn.c


OBJS		=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS) libft.h
		make -C ft_printf all
		cp ft_printf/*.a $(NAME)
		ar rc $(NAME) $(OBJS)

%.o:	%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	make -C ft_printf clean

fclean: clean
	rm -f $(NAME)
	make -C ft_printf fclean

re: fclean all
