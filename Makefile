# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmelica <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 14:06:13 by hmelica           #+#    #+#              #
#    Updated: 2023/09/15 14:25:10 by hmelica          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#
#    ____                _
#   |  _ \ ___  __ _  __| |_ __ ___   ___
#   | |_) / _ \/ _` |/ _` | '_ ` _ \ / _ \                   :)
#   |  _ <  __/ (_| | (_| | | | | | |  __/
#   |_| \_\___|\__,_|\__,_|_| |_| |_|\___|
#
# How to use :
# ----------
#   * all
#   * re
#   * clean
#   * fclean
#   * norm : like norminette but really fast to check all files
#   * bonus : all for bonus
#   * debug : like all but with -g flag, can be used with bonus too
#   * sanitize : use this as a parameter to compile executable with fsanitize
#
# Stuff to edit :
# -------------
NAME = minishell
NAME_BONUS = ${NAME}_bonus
#
# Mettre le nom des fichiers sans le dossier. Le dossier src est automatiquement
# ajouté.
# Mettre un seul fichier par ligne (pour les merge) et retourner à la ligne avec
# un "\" en fin de ligne précédente.
#
# Exemple :
#       main.c \       # oui
#       src/main.c     # non
SRCS_FILES = \
				env.c \
				envp.c \
				main.c \
				var.c \
				var_utils.c \
#
# ^- (this comment line matters)
#
# If needed, use macro BONUS that will be set to 1 when bonus is compiled.
# Every normal srcs_files are re-compiled with those additionnal files :
SRCS_FILES_BONUS = \
#
# ^- (this comment line matters too)
CFLAGS = -Wall -Werror -Wextra
# Other useful flags : -O3 -Wno-unused-result
#                           ^- flag de compilation sur mac (Apple Clang)
#                        ^- flag d'optimisation maximum (peut entrainer des
#                           comportements indéfinis)
DEBUG_FLAG = -g
SANITIZE_FLAG = -fsanitize=address
#
# **************************************************************************** #
#
# Le reste :
# --------

# N'affiche pas le changement de directory lors du ${MAKE} -c
MAKEFLAGS += --no-print-directory

CC = gcc

LIBFT_DIR = ${SRCS_DIR}/libft
LIBFT = ${SRCS_DIR}/libft/libft.a
LIBFT_TARGET = $(if $(filter debug,$(MAKECMDGOALS)),debug,all)

HEADERS_DIR = headers/ src/libft/
HEADERS_DIR_FLAG = ${addprefix -I ,${HEADERS_DIR}}

SRCS_DIR = src
SRCS = ${addprefix ${SRCS_DIR}/,${SRCS_FILES}}
SRCS_FILES_BONUS := ${SRCS_FILES_BONUS} ${addprefix b_,${SRCS_FILES}}
SRCS_BONUS = ${addprefix ${SRCS_DIR}/,${SRCS_FILES_BONUS}}

OBJS_DIR = obj
OBJS = ${patsubst ${SRCS_DIR}%.c,${OBJS_DIR}%.o,$(SRCS)}
OBJS_BONUS_VIRT = ${patsubst ${SRCS_DIR}%.c,${OBJS_DIR}%.o,$(SRCS_BONUS)}
OBJS_BONUS = ${patsubst b_%,%,$(OBJS_BONUS_VIRT)}

ECHO = echo
RM = rm -f
RMDIR = rm -df
MKDIR = mkdir

CFLAGS_NAME = $(if $(filter $(MAKECMDGOALS), sanitize),$(SANITIZE_FLAG),)
CFLAGS := ${CFLAGS} $(if $(filter $(MAKECMDGOALS), debug test),$(DEBUG_FLAG),)
DEBUG_PROMPT = \033[1;35mdebug mode\033[0m
OK_PROMPT = \033[1;32mdone \033[0m$(if $(filter $(MAKECMDGOALS), debug test),$(DEBUG_PROMPT),)

DELETE = \033[2K\r

all: ${NAME}
	@echo "\033[1;32mSuccess\033[0m"

${NAME}: ${LIBFT} ${OBJS_DIR} ${OBJS}
	@printf "$(DELETE)\033[1;33m...Building\033[0m %-23s" "${NAME}"
	@${CC} ${CFLAGS} ${CFLAGS_NAME} ${HEADERS_DIR_FLAG} -o ${NAME} ${OBJS} ${LIBFT}
	@echo "${OK_PROMPT}"
	@${MAKE} tags

bonus: ${NAME_BONUS}
	@echo "\033[1;32mSuccess\033[0m \033[1;35mbonus\033[0m"

${NAME_BONUS}: ${NAME}
	@printf "\033[1;33m...Building\033[0m %-23s" "${NAME_BONUS}"
	@cp ${NAME} ${NAME_BONUS}
	@echo "${OK_PROMPT} \033[1;35mbonus\033[0m"

${OBJS_DIR}:
	@printf "\033[1;34m...Creating\033[0m %-23s" "${OBJS_DIR} directory"
	@${MKDIR} ${OBJS_DIR}
	@printf "\033[1;32mdone\033[0m"

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@printf "$(DELETE)\033[1;34mCompiling\033[0m %-25s" $<
	@${CC} ${CFLAGS} ${HEADERS_DIR_FLAG} -c $< -o $@
	@printf "${OK_PROMPT}"

${OBJS_BONUS}: OK_PROMPT += \033[1;35mbonus\033[0m

${OBJS_DIR}/b_%.o: ${SRCS_DIR}/%.c
	@printf "\033[1;34mRecompiling\033[0m %-23s" $<
	@${CC} ${CFLAGS} ${HEADERS_DIR_FLAG} -D BONUS=1 -c $< -o $@
	@echo "${OK_PROMPT}"

${LIBFT}: force
	@${MAKE} -C ${LIBFT_DIR} ${LIBFT_TARGET}

norm:
	#@printf "\033[1;33mChecking norm...\033[0m %-18s" " "
	#@echo $$(a=$$(git ls-files | grep -E ".*\.[ch]$$" | grep -v "tests" |
	#xargs -n 4 -P 4 norminette | grep --color=always Error) ; b=$$(printf "%s" "$$a" | wc -l) ;
	#if [ $$b -eq 0 ]; then ${ECHO} "\033[1;32mdone\033[0m" ;
	#else ${ECHO} "\033[1;31mERROR\033[0m" ; printf "%s\n" "$$a" ; fi ; ) | sed
	#"s/Error/\nError/Ig"
	@printf "\n\033[1;33mChecking norm...\033[0m %-18s" " "
	@echo $$(a=$$(git ls-files | grep -E ".*\.[ch]$$" | grep -v "tests" | \
	xargs -n 4 -P 4 norminette | grep --color=always Error) ; b=$$(printf "%s" "$$a" | wc -l) ; \
	if [ $$b -eq 0 ]; then ${ECHO} "\033[1;32mdone\033[0m" ; \
	else ${ECHO} "\033[1;31mERROR\033[0m" ; printf "%s\n" "$$a" ; fi ; ) | sed \
	"s/Error/\nError/Ig"

clean:
	@${MAKE} -C ${LIBFT_DIR} clean
	@${RM} ${OBJS} ${OBJS_BONUS}
	@${RMDIR} ${OBJS_DIR}
	@printf "\033[1;34m%-34s\033[0m \033[1;32m%s\033[0m\n" "Cleaning" "done"

fclean: clean
	@${MAKE} -C ${LIBFT_DIR} fclean
	@${RM} ${NAME} ${NAME_BONUS}
	@${RM} tags
	@printf "\033[1;34m%-34s\033[0m \033[1;32m%s\033[0m\n" "File cleaning" "done"

re: fclean all

debug: all

sanitize:
	@printf "\033[1;34m%-34s\033[0m \033[1;32m%s\033[0m\n" "Output is sanitized" "done"

tags:force
	@printf "\033[1;33m.Generating\033[0m %-23s" "tags"
	@ctags --options=.ctags
	@echo "\033[1;32mdone\033[0m"

force:;

# supprime les fichiers dupliqués sur mac
mac_clean:
	@find . -type f -name "* [2-9]*" -print -delete

meson/meson.py:
	git submodule init
	git submodule update

criterion: meson/meson.py
	cd criterion ; python3 ../meson/meson.py setup build ; cd build ; python3 ../../meson/meson.py compile ; python3 ../../meson/meson.py test
