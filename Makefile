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

#all src files

SRC = src/main.cpp src/bot.cpp src/tools.cpp src/parse.cpp src/connection.cpp src/display.cpp src/message.cpp src/channel.cpp src/core.cpp

HEADER = inc/bot.hpp inc/tools.hpp

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJ)
	clang++ $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(HEADER) 
	clang++ $(FLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
