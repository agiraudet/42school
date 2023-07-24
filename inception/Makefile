# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 13:36:51 by agiraude          #+#    #+#              #
#    Updated: 2022/10/03 15:05:54 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ID		:= agiraude

SRC		:= srcs/docker-compose.yml

all: setup up

setup:
	mkdir -p /home/$(ID)/data/db
	mkdir -p /home/$(ID)/data/wp
	sed -i "/127.0.0.1 $(ID).42.fr/d" /etc/hosts
	echo "127.0.0.1 $(ID).42.fr" >> /etc/hosts

up:
	docker-compose -f $(SRC) up --build -d

down:
	docker-compose -f $(SRC) down

clean:
	docker-compose -f $(SRC) down --rmi all -v

fclean: clean
	rm -rf /home/$(ID)/data
	sed -i "/127.0.0.1 $(ID).42.fr/d" /etc/hosts

re:	fclean all


.PHONY: all clean fclean re up down
