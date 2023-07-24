# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/12 15:46:26 by agiraude          #+#    #+#              #
#    Updated: 2022/03/03 01:42:06 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a

BUILD_DIR	:=	./build

SRCS_DIR	:=	./srcs

SRCS		:=	ft_arradd.c \
				ft_arrdel.c \
				ft_arrflst.c \
				ft_arrlen.c \
				ft_arrsort.c \
				ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_countchar.c \
				ft_ctostr.c \
				ft_getindex.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_itoa_base.c \
				ft_itoa.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstlen.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstpop_back.c \
				ft_lstpop_front.c \
				ft_lstpop_srch.c \
				ft_lstsize.c \
				ft_lstswap.c \
				ft_ltrim.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_nsplit.c \
				ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl.c \
				ft_putendl_fd.c \
				ft_putnbr.c \
				ft_putnbr_fd.c \
				ft_putstr.c \
				ft_putstr_fd.c \
				ft_revstr.c \
				ft_rtrim.c \
				ft_split.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strndup.c \
				ft_strnstr.c \
				ft_strpop.c \
				ft_strrchr.c \
				ft_strrplc.c \
				ft_strstr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_trim.c \
				ft_utoa.c

OBJS		:=	$(SRCS:%.c=$(BUILD_DIR)/%.o)

INC_DIRS	:=	includes

INC_FLAGS	:= -I $(INC_DIRS)

CFLAGS		:=	$(INC_FLAGS) -Wall -Wextra -Werror

CC			:=	clang

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
