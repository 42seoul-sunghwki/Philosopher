# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:09:29 by sunghwki          #+#    #+#              #
#    Updated: 2024/03/22 20:05:46 by sunghwki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES = .c .o

CC = cc

CFLAGS = -Wall -Werror -Wextra

CLINK = -lpthread

SOURCE = helper.c thread.c ft_lib.c philo.c init.c thread_helper.c

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
