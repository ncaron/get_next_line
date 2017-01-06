# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Niko <niko.caron90@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/21 20:02:04 by Niko              #+#    #+#              #
#    Updated: 2017/01/02 16:18:34 by Niko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line

FLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS = main.c \
	   get_next_line.c

INCLUDES = get_next_line.h

LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C ./libft

$(NAME):
	gcc $(FLAGS) $(SRCS) -g -o $(NAME) $(LIBFT)

clean:
	make clean -C ./libft

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all
