# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 20:35:38 by asabri            #+#    #+#              #
#    Updated: 2023/11/09 03:34:44 by abberkac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC   = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM   = rm -f
SRCS = src/render.c main.c src/ray_casting.c parsing.c utils.c get_next_line.c get_next_line_utils.c  #lst_functions.c
OBJ  = $(SRCS:.c=.o)
INC  = include/cub3d.h

LIBMLX = /Users/abberkac/Desktop/libmlx42.a
LIBMLX_INC = -I /Users/abberkac/MLX42/include/MLX42 -I ./include/
MLXFLG = -Iinclude -lglfw -L"/Users/$(USER)/goinfre/homebrew/opt/glfw/lib" -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(MLXFLG) $(LIBMLX)  $^ -o $@

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBMLX_INC)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean all clean re

