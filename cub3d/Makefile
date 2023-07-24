# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 10:43:09 by agiraude          #+#    #+#              #
#    Updated: 2021/01/22 10:55:44 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_DIR		= 	minilibx-linux/

LIBFT_DIR	=	libft/

LIBFT		=	libft.a

MLX			=	libmlx_Linux.a

INC_DIR		=	includes/ -I $(MLX_DIR)

SRCS_DIR	=	srcs/

SRCS_FILES	=	main.c \
				bonus/anim_bonus.c \
				bonus/minimap_bonus.c \
				bonus/parser_bonus.c \
				bonus/rect_bonus.c \
				bonus/render_bonus.c \
				engine/loop.c \
				engine/raycast.c \
				engine/render.c \
				managers/destroy.c \
				managers/inits.c \
				managers/player.c \
				managers/player_set.c \
				managers/settings.c \
				managers/texture.c \
				sprites/sprite.c \
				sprites/sprite_render.c \
				utils/bitmap.c \
				utils/check_map.c \
				utils/get_next_line.c \
				utils/get_next_line_utils.c \
				utils/map.c \
				utils/parser.c \
				utils/utils.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS_BONUS	=	$(SRCS:.c=_b.o)

OBJS		=	$(SRCS:.c=.o)

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

NAME		=	cub3d

DEP			=	-lft -lmlx_Linux -lXext -lX11 -lm

%.o:			%.c
				$(CC) $(CFLAGS) -D BONUS=0 -c $< -o $(<:.c=.o) -I $(INC_DIR)

%_b.o:			%.c
				$(CC) $(CFLAGS) -D BONUS=1 -c $< -o $(<:.c=_b.o) -I $(INC_DIR)


all:			$(NAME)

$(LIBFT):
				make -C $(LIBFT_DIR)

$(MLX):
				make -C $(MLX_DIR)

$(NAME):		$(OBJS) $(LIBFT) $(MLX)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(MLX_DIR) -L $(LIBFT_DIR) $(DEP) -I $(INC_DIR)

gflag:			$(OBJS) $(LIBFT) $(MLX)
				$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) -L $(MLX_DIR) -L $(LIBFT_DIR) $(DEP) -I $(INC_DIR)

bonus:			$(OBJS_BONUS) $(LIBFT) $(MLX)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS_BONUS) -L $(MLX_DIR) -L $(LIBFT_DIR) $(DEP) -I $(INC_DIR)

debug:			
				make fclean
				make gflag
clean:
				$(RM) $(OBJS)
				$(RM) $(OBJS_BONUS)
				make clean -C $(LIBFT_DIR)
				make clean -C $(MLX_DIR)

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(LIBFT_DIR)$(LIBFT)

re:				fclean all

.PHONY:			all clean fclean re
