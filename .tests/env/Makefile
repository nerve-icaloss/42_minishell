# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmelica <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 11:54:20 by hmelica           #+#    #+#              #
#    Updated: 2023/09/14 12:04:52 by hmelica          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c

OBJS = ${SRCS:.c=.o}
OTHERS = ../../obj/var.o ../../obj/env.o ../../src/libft/libft.a
HEADER = ../../headers/ ../../src/libft/

HEADER_DIR = ${addprefix -I ,${HEADER}}

all: env_test
	# all done

env_test: ${OBJS}
	${MAKE} -C ../../
	gcc -Wall -Wextra -Werror -g ${HEADER_DIR} ${OBJS} ${OTHERS} -o env_test

.c.o:
	gcc -Wall -Wextra -Werror -g -c $< -o ${<:.c=.o}

fclean:
	rm -rf *.o env_test

re: fclean all
