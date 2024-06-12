# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 15:56:24 by nuno              #+#    #+#              #
#    Updated: 2024/06/12 22:22:02 by nhorta-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	PmergeMe
CXX			=	c++

SRCS		=	main.cpp \
				PmergeMe.cpp

CXXFLAGS	=	-Wall -Wextra -Werror -g -std=c++98 -g -fsanitize=address

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