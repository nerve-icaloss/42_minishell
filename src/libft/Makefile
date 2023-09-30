# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmelica <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 10:50:51 by hmelica           #+#    #+#              #
#    Updated: 2023/09/24 19:34:36 by hmelica          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c \
	ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
	ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
	ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_split_e.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
	ft_toupper.c gnl.c gnl_utils.c ft_printf.c is_something.c flags.c \
	min_width.c digit.c char.c string.c pointer.c unsigned.c hexa.c ft_atol.c \
	ft_dprintf.c ft_arrclear.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

CC = gcc

RM = rm -f

NAME = libft.a

INCLUDES = libft.h

LIBC = ar

LIBFLAGS = rcs

OK_PROMPT = \033[1;32mdone\033[0m
CFLAGS := ${CFLAGS} $(if $(filter debug,$(MAKECMDGOALS)),-g,)
DEBUG_PROMPT = \033[1;35mdebug mode\033[0m
OK_PROMPT = \033[1;32mdone \033[0m$(if $(filter debug,$(MAKECMDGOALS)),$(DEBUG_PROMPT),)

DELETE = \033[2K\r

all: ${NAME}
	@echo > /dev/null

${NAME}:${OBJS}
	@printf "$(DELETE)\033[1;33m...Building\033[0m %-23s" "libft"
	@${LIBC} ${LIBFLAGS} ${NAME} ${OBJS}
	@echo "${OK_PROMPT}"

.c.o:
	@printf "$(DELETE)\033[1;34mRecompiling\033[0m %-23s" $<
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	@printf "${OK_PROMPT}"

clean:
	@${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

debug: all
	@exit;
