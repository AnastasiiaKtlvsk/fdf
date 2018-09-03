# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akotilie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/01 19:50:05 by akotilie          #+#    #+#              #
#    Updated: 2018/08/12 12:08:45 by akotilie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

FLAGS = -Wall -Werror -Wextra

FDF =  start.c read_map.c process_map.c

LIBFT = libft/libft.a

MNLX = minilibx/mlx.

COMPILED = $(FDF:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft/
	gcc $(FLAGS) -lmlX $(FDF) -framework OpenGL -framework Appkit $(LIBFT) -o $(NAME)

clean:
	make clean -C libft/

fclean:
	make fclean -C libft/
	rm -rf $(NAME)

re: fclean all
