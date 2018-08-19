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

FILLER =  start.c read_map.c

LIBFT = libft/libft.a

COMPILED = $(FILLER:.c=.o)

all:	$(NAME)

$(NAME): $(COMPILED) $(LIBFT)
	@gcc $(FLAGS) -o $(NAME) $(COMPILED) $(LIBFT)

$(LIBFT):	liball

liball:
	@make -C ./libft

clean:
	@rm -f *.o
	@make clean -C ./libft

fclean:	clean
	@make fclean -C ./libft
	@rm  -f $(NAME)

re: fclean all
