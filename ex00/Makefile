# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 15:21:23 by luserbu           #+#    #+#              #
#    Updated: 2023/04/19 14:51:51 by luserbu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.cpp BitcoinExchange.cpp

OBJS	= $(SRCS:.cpp=.o)

NAME 	= btc

CC		= c++ -std=c++98 -Wall -Werror -Wextra -g

all : $(NAME)

%.o: %.cpp
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
