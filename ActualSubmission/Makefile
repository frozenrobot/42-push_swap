# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/03 16:22:06 by kgulati           #+#    #+#              #
#    Updated: 2021/06/03 18:17:22 by kgulati          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap.a
INCLUDES = push_swap.h
FILES = ps_utils_1.c \
		ps_utils_2.c \
		ps_utils_3.c \
		ps_utils_4.c \
		ps_utils_5.c \
		ps_utils_7.c \
		ps_utils_8.c \
		ps_utils_9.c \
		ps_utils_10.c \
		ps_utils_11.c \
		ps_utils_12.c

OBJ = $(FILES:.c=.o)

all : $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra -c $(FILES)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all