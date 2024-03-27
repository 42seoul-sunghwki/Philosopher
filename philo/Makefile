# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 15:09:29 by sunghwki          #+#    #+#              #
#    Updated: 2024/03/27 11:16:13 by sunghwki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra

CLINK = -lpthread

SOURCE = main.c main_util.c \
			philo.c philo_util.c philo_state.c \
			ft_lib.c ft_lib2.c

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

.PHONY : all clean fclean re
