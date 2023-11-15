# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabri <asabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 20:35:38 by asabri            #+#    #+#              #
#    Updated: 2023/11/15 08:43:54 by asabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC   = gcc
CFLAGS = -Wall -Wextra -Werror 
RM   = rm -f
SRCS = main.c src/render.c src/ray_casting.c src/parsing.c src/utils.c src/get_next_line.c src/get_next_line_utils.c src/check_infos.c src/check_map.c
OBJ  = $(SRCS:.c=.o)
INC  = include/cub3d.h

LIBMLX = ../MLX42/build/libmlx42.a
LIBMLX_INC = -I ../MLX42/include/MLX42 -I ./include/
MLXFLG = -Iinclude -lglfw $(GFLW) -framework Cocoa -framework OpenGL -framework IOKit

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

