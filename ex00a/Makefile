# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 15:56:24 by nuno              #+#    #+#              #
#    Updated: 2024/06/06 13:45:51 by nuno             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	btc

CXX			=	c++

SRCS		=	main.cpp \
				btc.cpp

CXXFLAGS	=	-Wall -Wextra -Werror -g -std=c++98 -fsanitize=address

RM			=	rm -f

OBJS		=	$(SRCS:%.cpp=%.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(OBJS) $(CXXFLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re