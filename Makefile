# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlamkadm <mlamkadm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 20:24:35 by mlamkadm          #+#    #+#              #
#    Updated: 2024/09/19 20:24:35 by mlamkadm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bin/bot

SRC_DIR = src
HEADER = inc/bot.hpp inc/tools.hpp
OBJ_DIR = obj

SRC = main.cpp bot.cpp tools.cpp parse.cpp connection.cpp display.cpp message.cpp channel.cpp core.cpp

OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

FLAGS = -Wall -Wextra #-Werror

CPP98 = -std=c++98

ARGS = -C conf/config.txt

build: all clean

all: $(NAME)

run: all clean
	./$(NAME) $(ARGS)

$(NAME): $(OBJ)
	@mkdir -p $(dir $(NAME))
	clang++ $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	clang++ $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all build run clean fclean re

