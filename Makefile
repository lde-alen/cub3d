# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-alen <lde-alen@student.42.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/27 16:35:14 by lde-alen          #+#    #+#              #
#    Updated: 2023/05/28 17:32:37 by lde-alen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Executable name
NAME			=		cub3d


## Directories
LIBFT_DIR		=		libft/
GNL_DIR			=		get_next_line/
MLX_DIR			=		minilibx_opengl/
MLX_LIN_DIR		=		minilibx_linux/
SRCS_DIR		=		srcs/

## Archives
LIBFT_NAME		=		libft.a
MLX_NAME		=		libmlx.a

OBJS			=		$(SRCS:.c=.o)

## Files
SRCS			=		srcs/cub3d.c						\
						srcs/control_map.c					\
						srcs/cub3d_utils.c					\
						srcs/events.c						\
						srcs/fill_map.c						\
						srcs/init.c							\
						srcs/mlx.c							\
						srcs/parse.c						\
						srcs/texture.c						\
						srcs/move.c							\
						srcs/raycasting/raycasting.c		\
						srcs/raycasting/raycasting_utils.c	\




## Runs uname command on the terminal in order to determine the OS ##
UNAME 			:=		$(shell uname)

## Flags
FLAGS			=		-Wall -Wextra -Werror

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