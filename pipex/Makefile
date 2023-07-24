# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 10:43:09 by agiraude          #+#    #+#              #
#    Updated: 2022/02/01 00:11:52 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR	=	libft/

LIBFT		=	libft.a

INC_DIR		=	-I includes/ -I $(LIBFT_DIR)includes/

SRCS_DIR	=	srcs/

SRCS_FILES	=	cmd.c \
				main.c \
				parse.c \
				pipex.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS		=	$(SRCS:.c=.o)

CC			=	clang

CFLAGS		=	-Wall -Wextra -g

RM			=	rm -f

NAME		=	pipex

DEP			=	-lft 

%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INC_DIR)

all:			$(NAME)

$(LIBFT):
				make -C $(LIBFT_DIR)

$(NAME):		$(OBJS) $(LIBFT) $(PUSH_O)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(LIBFT_DIR) $(DEP) $(INC_DIR)

clean:
				$(RM) $(OBJS)
				$(RM) $(NAME)
				make clean -C $(LIBFT_DIR)

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(LIBFT_DIR)$(LIBFT)

re:				fclean all

.PHONY:			all clean fclean re
