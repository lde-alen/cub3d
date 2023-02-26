# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-alen <lde-alen@student.42abudhabi.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/12 08:48:30 by lde-alen          #+#    #+#              #
#    Updated: 2023/02/19 14:55:51 by lde-alen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Executable name
NAME			=		cub3d


## Directories
LIBFT_DIR		=		libft/
MLX_DIR			=		minilibx_opengl_20191021/
SRCS_DIR		=		srcs/

## Archives
LIBFT_NAME		=		libft.a
MLX_NAME		=		libmlx.a

OBJS			=		$(SRCS:.c=.o)

## Files
SRCS			=		srcs/main.c			\
						srcs/parser/check.c	\



## Runs uname command on the terminal in order to determine the OS ##
UNAME 			:=		$(shell uname)

## Flags
FLAGS			=		-Wall -Wextra -Werror -g3

## If the OS is Linux, then the MLX library is compiled with the following flags
## otherwise, it is compiled with the MacOS flags
ifeq ($(UNAME),Linux)
	MLX_COMPIL	=		-L $(MLX_DIR) -lm -lXext -lX11
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
