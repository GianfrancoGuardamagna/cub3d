# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 12:00:00 by gguardam          #+#    #+#              #
#    Updated: 2026/07/03 13:13:31 by gguardam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCE = main.c events.c renders.c aux.c player.c
OBJ = $(SOURCE:.c=.o)
INCLUDE = cub3d.h
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./MLX42
MLX = $(MLX_DIR)/build/libmlx42.a
LIBS = -L$(MLX_DIR)/build -lmlx42 -L$(LIBFT_DIR) -Iinclude -ldl -lglfw -pthread -lm
INCLUDES = -I. -I$(LIBFT_DIR) -I$(MLX_DIR)
RM = rm -f

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	@cd $(MLX_DIR) && cmake -B build
	@cd $(MLX_DIR) && cmake --build build -j4

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean
	$(RM) -r $(MLX_DIR)/build

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean
	$(RM) -r $(MLX_DIR)/build

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus