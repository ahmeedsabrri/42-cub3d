# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asabri <asabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 20:35:38 by asabri            #+#    #+#              #
#    Updated: 2023/10/17 00:30:39 by asabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC   = gcc -Wall -Wextra -Werror 
RM   = rm -f
SRCS = src/main.c src/ray_casting.c 
OBJ  = $(SRCS:.c=.o)
INC  = include/cub3d.h

LIBMLX = /Users/asabri/MLX42/build/libmlx42.a
LIBMLX_INC = -I /Users/asabri/MLX42/include/MLX42 -I ./include/
MLXFLG = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(MLXFLG) $(LIBMLX)  $^ -o $@

%.o: %.c $(INC)
	$(CC) -c $< -o $@ $(LIBMLX_INC)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: fclean all clean re

