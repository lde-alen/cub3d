# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myvh <myvh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 08:48:30 by lde-alen          #+#    #+#              #
#    Updated: 2023/05/09 21:11:05 by myvh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Executable name
NAME			=		cub3d


## Directories
LIBFT_DIR		=		libft/
GNL_DIR			=		get_next_line/
MLX_DIR			=		minilibx-linux/
MLX_LIN_DIR			=		minilibx-linux/
SRCS_DIR		=		srcs/

## Archives
LIBFT_NAME		=		libft.a
MLX_NAME		=		libmlx.a

OBJS			=		$(SRCS:.c=.o)

## Files
SRCS			=		srcs/ft_cub3d.c			\
								srcs/ft_control_map.c	\
								srcs/ft_cub3d_utils.c				\
								srcs/ft_events.c	\
								srcs/ft_fill_map.c						\
								srcs/ft_find_wall.c\
								srcs/ft_init.c\
								srcs/ft_mlx.c\
								srcs/ft_move.c\
								srcs/ft_parse.c\
								srcs/ft_print_wall.c\
								srcs/ft_save_bitmap.c\
								srcs/ft_sprite_1.c\
								srcs/ft_sprite_2.c\
								srcs/ft_texture.c\




## Runs uname command on the terminal in order to determine the OS ##
UNAME 			:=		$(shell uname)

## Flags
FLAGS			=		-Wall -Wextra -Werror -g3

## If the OS is Linux, then the MLX library is compiled with the following flags
## otherwise, it is compiled with the MacOS flags
ifeq ($(UNAME),Linux)
	MLX_COMPIL	=		-L $(MLX_LIN_DIR) -lm -lXext -lX11
else
	MLX_COMPIL	=		-L $(MLX_DIR) -l mlx -framework OpenGL -framework AppKit
endif

## Path to Includes folder
INCLUDES		=		-I./includes

## Quality of life and dopamine
RM				=		rm -f
CC				=		gcc



## Transforms .c into .o
.c.o			:
						$(CC) $(FLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

## 
$(NAME)			:		$(OBJS)
						@$(MAKE) -C ./libft
						@$(MAKE) -C $(MLX_DIR)
						@$(CC) $(MLX_COMPIL) $(FLAGS) $(INCLUDES) $(OBJS) $(MLX_DIR)/$(MLX_NAME) $(LIBFT_DIR)/$(LIBFT_NAME) -o $(NAME)

## Calls Name
all				:		$(NAME)

## Removes all .o files
clean			:
						$(MAKE) clean -C $(LIBFT_DIR)
						$(MAKE) clean -C $(MLX_DIR)
						rm -rf $(OBJS)	

## Removes all .o files and the executable
fclean			:		clean
						rm -rf $(NAME)
## Calls fclean and all
re				:		fclean all

.PHONY:		all fclean clean re