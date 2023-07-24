# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 15:43:27 by agiraude          #+#    #+#              #
#    Updated: 2022/11/17 13:30:59 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	ircserv

BUILD_DIR	:=	./build

SRCS_DIR	:=	./srcs

SRCS		:=	main.cpp \
				CoHandler.cpp \
				CmdHandler.cpp \
				Chan.cpp \
				Logger.cpp \
				Mask.cpp \
				Server.cpp \
				User.cpp \
				utils.cpp \
				cmds/invite.cpp \
				cmds/join.cpp \
				cmds/kick.cpp \
				cmds/kill.cpp \
				cmds/list.cpp \
				cmds/mode.cpp \
				cmds/motd.cpp \
				cmds/names.cpp \
				cmds/nick.cpp \
				cmds/notice.cpp \
				cmds/oper.cpp \
				cmds/part.cpp \
				cmds/pass.cpp \
				cmds/ping.cpp \
				cmds/pong.cpp \
				cmds/privmsg.cpp \
				cmds/quit.cpp \
				cmds/topic.cpp \
				cmds/user.cpp \
				cmds/who.cpp  

OBJS		:=	$(SRCS:%.cpp=$(BUILD_DIR)/%.o)

INC_DIRS	:=	./includes 

INC_FLAGS	:=	$(addprefix -I, $(INC_DIRS))

CXXFLAGS	:=	-MD -Wall -Wextra -Werror -std=c++98 $(INC_FLAGS)

CXX			:=	c++

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(DEPS) -o $@


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/cmds

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

all: $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
