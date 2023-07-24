# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/04 10:43:09 by agiraude          #+#    #+#              #
#    Updated: 2021/12/17 13:27:14 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR	=	libft/

LIBFT		=	libft.a

INC_DIR		=	-I includes/ -I $(LIBFT_DIR)includes/

SRCS_DIR	=	srcs/

SRCS_FILES	=	stack.c \
				stack2.c \
				stack3.c \
				stack4.c \
				chunck.c \
				chunck_sort.c \
				controls.c \
				utils.c \
				utils2.c \
				utils3.c \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c \
				sort.c

CHECK_C		=	$(addprefix $(SRCS_DIR), checker.c)

PUSH_C		=	$(addprefix $(SRCS_DIR), push_swap.c)

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS		=	$(SRCS:.c=.o)

CHECK_O		=	$(CHECK_C:.c=.o)

PUSH_O		=	$(PUSH_C:.c=.o)

CC			=	clang

CFLAGS		=	-Wall -Wextra -g

RM			=	rm -f

NAME		=	test

DEP			=	-lft 

%.o:			%.c
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INC_DIR)

all:			push_swap

$(LIBFT):
				make -C $(LIBFT_DIR)

bonus:			$(OBJS) $(LIBFT) $(CHECK_O)
				$(CC) $(CFLAGS) -o checker $(OBJS) $(CHECK_O) -L $(LIBFT_DIR) $(DEP) $(INC_DIR)

push_swap:		$(OBJS) $(LIBFT) $(PUSH_O)
				$(CC) $(CFLAGS) -o push_swap $(OBJS) $(PUSH_O) -L $(LIBFT_DIR) $(DEP) $(INC_DIR)
clean:
				$(RM) $(OBJS)
				$(RM) $(CHECK_O) $(PUSH_O)
				make clean -C $(LIBFT_DIR)

fclean:			clean
				$(RM) push_swap
				$(RM) checker
				$(RM) $(LIBFT_DIR)$(LIBFT)

re:				fclean all

.PHONY:			all clean fclean re
