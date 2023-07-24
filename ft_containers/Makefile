# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 15:43:27 by agiraude          #+#    #+#              #
#    Updated: 2023/02/01 09:33:10 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cont

NAME_FT		:= $(addsuffix FT, $(NAME))

NAME_STD	:= $(addsuffix STD, $(NAME))

DEMO_FT		:=	mainFT

DEMO_STD	:=	mainSTD

SRCS_DIR	:=	./srcs

SRCS_N		:=	test.cpp

SRCS_D		:=	main.cpp

INC_DIRS	:=	./includes 

INC_FLAGS	:=	$(addprefix -I, $(INC_DIRS))

CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -g $(INC_FLAGS)

CXX			:=	c++

$(NAME): $(NAME_FT) $(NAME_STD) $(DEMO_FT) $(DEMO_STD)

$(NAME_FT): $(OBJS_N)
	$(CXX) $(CXXFLAGS) -DFT $(SRCS_DIR)/$(SRCS_N) $(DEPS) -o $@

$(NAME_STD): $(OBJS_N)
	$(CXX) $(CXXFLAGS) -DSTD $(SRCS_DIR)/$(SRCS_N) $(DEPS) -o $@

$(DEMO_FT): $(OBJS_D)
	$(CXX) $(CXXFLAGS) -DFT $(SRCS_DIR)/$(SRCS_D) $(DEPS) -o $@

$(DEMO_STD): $(OBJS_D)
	$(CXX) $(CXXFLAGS) $(SRCS_DIR)/$(SRCS_D) $(DEPS) -o $@

all: $(NAME)

test: $(NAME)
	time -p ./$(DEMO_FT) 1234 && time -p ./$(DEMO_STD) 1234 && ./$(NAME_FT) 100 0 && ./$(NAME_STD) 100 0

clean:

fclean: clean
	rm -f $(NAME_FT)
	rm -f $(NAME_STD)
	rm -f $(DEMO_FT)
	rm -f $(DEMO_STD)

re: fclean all

.PHONY: all clean fclean re
