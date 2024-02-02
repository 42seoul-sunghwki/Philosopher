# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:09:29 by sunghwki          #+#    #+#              #
#    Updated: 2024/02/02 23:08:07 by sunghwki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES = .c .o

CC = clang

CFLAGS = -Wall -Werror -Wextra

CLINK = -lpthread

SOURCE = helper.c \
			philo.c \
			thread.c

OBJECTS = $(SOURCE:.c=.o)

NAME = philo

$(NAME) : $(OBJECTS)
			$(CC) $(CFLAGS) -o $(NAME) $(SOURCE) $(CLINK)

all : $(NAME)

clean :
	rm -rf $(OBJECTS)

fclean :
	make clean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean 
