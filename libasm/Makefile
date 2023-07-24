# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 22:59:36 by agiraude          #+#    #+#              #
#    Updated: 2021/02/04 11:30:10 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libasm.a

SRCS_FILES		=	ft_strlen.s \
					ft_strcpy.s \
					ft_write.s \
					ft_read.s \
					ft_strdup.s \
					ft_strcmp.s \

SRCS_FILE_BONUS	=	ft_list_create_elem_bonus.s \
					ft_list_swap_bonus.s \
					ft_list_remove_if_bonus.s \
					ft_list_delone_bonus.s \
					ft_list_push_front_bonus.s \
					ft_list_size_bonus.s \
					ft_list_sort_bonus.s \
					ft_atoi_base_bonus.s \
					ft_isspace_bonus.s \
					ft_getindex_bonus.s \
					ft_checkbase_bonus.s

SRCS_FILE_TEST	=	main.c \
					main_test.c

SRCS_FILE_T_BON	=	ft_atoi_base.c \
					main_bonus.c \
					main_bonus_list.c

SRCS_DIR		=	srcs/

SRCS_DIR_BONUS	=	bonus/

SRCS_DIR_TEST	=	tester/

SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_FILES))

SRCS_BONUS		=	$(addprefix $(SRCS_DIR)$(SRCS_DIR_BONUS), $(SRCS_FILE_BONUS))

SRCS_TEST		=	$(addprefix $(SRCS_DIR)$(SRCS_DIR_TEST), $(SRCS_FILE_TEST))

SRCS_TEST_BONUS	=	$(addprefix $(SRCS_DIR)$(SRCS_DIR_TEST), $(SRCS_FILE_T_BON))

OBJS			=	$(SRCS:.s=.o)

OBJS_BONUS		=	$(SRCS_BONUS:.s=.o)

NASM			=	nasm

ASM_FLAGS		=	-f elf64

%.o:			%.s
				$(NASM) $(ASM_FLAGS) $< -o $(<:.s=.o)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

all:			$(NAME)

clean:
				rm -f $(OBJS)
				rm -f $(OBJS_BONUS)

fclean:			clean
				rm -f $(NAME)
				rm -f test
				rm -f test_bonus

re:				fclean all

test:			$(NAME)
				clang -Wall -Wextra -Werror $(SRCS_TEST) -I includes -L . -lasm -o test

test_bonus:		$(NAME)
				clang -Wall -Wextra -Werror $(SRCS_TEST_BONUS) -I includes -L . -lasm -o test_bonus

bonus:			$(OBJS) $(OBJS_BONUS)
				ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

.PHONY:			all clean fclean re
