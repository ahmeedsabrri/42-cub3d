# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abberkac <abberkac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 20:35:38 by asabri            #+#    #+#              #
#    Updated: 2023/11/19 22:23:07 by abberkac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC   = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
RM   = rm -f
SRCS = main.c src/ray_casting.c src/ray_casting_utils.c src/ray_casting_utils1.c src/ray_casting_utils2.c \
		src/render.c src/render_utils.c src/render_utils1.c src/render_utils2.c src/parsing.c src/utils.c src/get_next_line.c src/get_next_line_utils.c \
		src/check_infos.c src/check_map.c src/parse_util.c src/utils_2.c src/utils_3.c src/utils_4.c
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

