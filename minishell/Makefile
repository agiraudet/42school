# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 15:43:27 by agiraude          #+#    #+#              #
#    Updated: 2022/09/10 15:35:08 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

BUILD_DIR	:=	./build

LIBFT_DIR	:=	./libft

LIBFT		:=	$(LIBFT_DIR)/libft.a

SRCS_DIR	:=	./srcs

SRCS		:=	args.c \
				cmd.c \
				error.c \
				exec.c \
				exit_code.c \
				expand.c \
				main.c \
				parse.c \
				path.c \
				path2.c \
				pipes.c \
				redir.c \
				redir2.c \
				signals.c \
				tilde.c \
				utils.c \
				utils2.c \
				heredoc.c \
				builtins/builtins.c \
				builtins/cd.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/exit.c \
				builtins/export.c \
				builtins/pwd.c \
				builtins/unset.c \
				env/env.c \
				env/env_chg.c \
				env/env_get.c \

OBJS		:=	$(SRCS:%.c=$(BUILD_DIR)/%.o)


DEPS				=	-L $(LIBFT_DIR) -lft -lreadline  -L/usr/local/opt/readline/lib -I/includes/mush.h -I/usr/local/opt/readline/include

INC_DIRS	:=	./includes $(LIBFT_DIR)/includes  /usr/local/opt/readline/lib /usr/local/opt/readline/include

INC_FLAGS	:=	$(addprefix -I, $(INC_DIRS))

CFLAGS		:=	$(INC_FLAGS) -Wall -Wextra -Werror -g3

CC			:= cc

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(DEPS) -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/env
	mkdir -p $(BUILD_DIR)/builtins

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
