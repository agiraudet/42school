# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 15:43:27 by agiraude          #+#    #+#              #
#    Updated: 2022/10/01 20:39:04 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	animals

BUILD_DIR	:=	./build

SRCS_DIR	:=	./srcs

SRCS		:=	main.cpp \
				AAnimal.cpp \
				Brain.cpp \
				Cat.cpp \
				Dog.cpp

OBJS		:=	$(SRCS:%.cpp=$(BUILD_DIR)/%.o)

INC_DIRS	:=	./includes 

INC_FLAGS	:=	$(addprefix -I, $(INC_DIRS))

CFLAGS		:=	$(INC_FLAGS) -Wall -Wextra -Werror -std=c++98 -g

CC			:=	c++

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(DEPS) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
