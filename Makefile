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

NAME = Bot

SRC = main.cpp src/bot.cpp src/tools.cpp

HEADER = inc/bot.hpp inc/tools.hpp

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Wextra -Werror

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
