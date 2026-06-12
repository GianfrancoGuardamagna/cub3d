# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/06 12:00:00 by gguardam          #+#    #+#              #
#    Updated: 2026/06/02 11:59:22 by gguardam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
SOURCE = 	main.c events.c
OBJ = $(SOURCE:.c=.o)
INCLUDE = cub3d.h
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
LIBS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm
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
	make -C $(MLX_DIR)

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus