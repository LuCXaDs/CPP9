# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 15:21:23 by luserbu           #+#    #+#              #
#    Updated: 2023/04/21 12:30:15 by luserbu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.cpp RPN.cpp

OBJS	= $(SRCS:.cpp=.o)

NAME 	= RPN

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
