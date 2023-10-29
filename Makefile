# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/13 14:06:13 by hmelica           #+#    #+#              #
#    Updated: 2023/10/29 10:12:33 by hmelica          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
NAME		= minishell
NAME_BONUS	= ${NAME}_bonus
#
# Mettre le nom des fichiers sans le dossier. Le dossier src est automatiquement
# ajouté.
# Mettre un seul fichier par ligne (pour les merge) et retourner à la ligne avec
# un "\" en fin de ligne précédente.
#
# Exemple :
#       main.c \       # oui
#       src/main.c     # non
SRCS_FILES	=	\
				1-data/builtin.c \
				1-data/env.c \
				1-data/env_envp.c \
				1-data/execute.c \
				1-data/expand.c \
				1-data/history.c \
				1-data/node.c \
				1-data/node_sibling.c \
				1-data/node_tree.c \
				1-data/shell.c \
				1-data/source.c \
				1-data/source_tokbuf.c \
				1-data/token.c \
				1-data/var.c \
				1-data/wildcard.c \
				1-data/wildcard_glob.c \
				2-builtin/blt_cd.c \
				2-builtin/blt_echo.c \
				2-builtin/blt_env.c \
				2-builtin/blt_exit.c \
				2-builtin/blt_export.c \
				2-builtin/blt_pwd.c \
				2-builtin/blt_unset.c \
				3-front/header.c \
				3-front/parser.c \
				3-front/parser_error.c \
				3-front/parser_redir.c \
				3-front/parser_utils.c \
				3-front/scanner.c \
				3-front/scanner_utils.c \
				4-back/executor.c \
				4-back/executor_blt.c \
				4-back/executor_child.c \
				4-back/executor_path.c \
				4-back/executor_utils.c \
				4-back/expander.c \
				4-back/expander_quote.c \
				4-back/expander_var.c \
				4-back/expander_wc.c \
				4-back/here_doc.c \
				4-back/redirection.c \
				4-back/redirection_utils.c \
				4-back/signal.c \
				5-utils/utl_access.c \
				5-utils/utl_close.c \
				5-utils/utl_doc.c \
				5-utils/utl_error.c \
				5-utils/utl_find.c \
				5-utils/utl_fork.c \
				5-utils/utl_open.c \
				5-utils/utl_path.c \
				5-utils/utl_read.c \
				5-utils/utl_tmp.c \
				5-utils/utl_var.c \
				5-utils/utl_wildcard.c \
				5-utils/utl_words.c \
				main.c \
#
# ^- (this comment line matters)
#
# If needed, use macro BONUS that will be set to 1 when bonus is compiled.
# Every normal srcs_files are re-compiled with those additionnal files :
SRCS_FILES_BONUS = \
#
# ^- (this comment line matters too)
CFLAGS	= -Wall -Werror -Wextra
# Other useful flags : -O3 -Wno-unused-result
#                           ^- flag de compilation sur mac (Apple Clang)
#                        ^- flag d'optimisation maximum (peut entrainer des
#                           comportements indéfinis)
DEBUG_FLAG		= -g3
SANITIZE_FLAG	= -fsanitize=address
#
# **************************************************************************** #
#
# Le reste :
# --------

# N'affiche pas le changement de directory lors du ${MAKE} -c
MAKEFLAGS += --no-print-directory

CC = cc

TEST_MODE = -D TEST_MODE
# comment to disable test and compile with static

LIBFT_DIR		= ${SRCS_DIR}/libft
LIBFT_FLAG		= -L $(LIBFT_DIR) -l:libft.a
LIBFT			= ${SRCS_DIR}/libft/libft.a
LIBFT_TARGET	= $(if $(filter debug,$(MAKECMDGOALS)),debug,all)

HEADERS_DIR			= headers/ src/libft/ criterion/include/
HEADERS_DIR_FLAG	= ${addprefix -I ,${HEADERS_DIR}}

LIBRARY_SEARCH_PATH	= -L test/lib/x86_64-linux-gnu/
LIBRARY_TESTS		= -lcriterion

SRCS_DIR			= src
SRCS				= ${addprefix ${SRCS_DIR}/,${SRCS_FILES}}
SRCS_FILES_BONUS	:= ${SRCS_FILES_BONUS} ${addprefix b_,${SRCS_FILES}}
SRCS_BONUS			= ${addprefix ${SRCS_DIR}/,${SRCS_FILES_BONUS}}

OBJS_DIR		= obj
OBJS			= ${patsubst ${SRCS_DIR}%.c,${OBJS_DIR}%.o,$(SRCS)}
OBJS_BONUS_VIRT	= ${patsubst ${SRCS_DIR}%.c,${OBJS_DIR}%.o,$(SRCS_BONUS)}
OBJS_BONUS		= ${patsubst b_%,%,$(OBJS_BONUS_VIRT)}

ECHO	= echo
RM		= rm -f
RMDIR	= rm -df
MKDIR	= mkdir

CFLAGS_NAME		= $(if $(filter $(MAKECMDGOALS), sanitize),$(SANITIZE_FLAG),)
CFLAGS			:= ${CFLAGS} $(if $(filter $(MAKECMDGOALS), debug test),$(DEBUG_FLAG),) ${TEST_MODE}
DEBUG_PROMPT	= \033[1;35mdebug mode\033[0m
OK_PROMPT		= \033[1;32mdone \033[0m$(if $(filter $(MAKECMDGOALS), debug test),$(DEBUG_PROMPT),)
OK_PROMPT += $(ifdef TEST_MODE, "\033[1;35munit test mode\033[0m")

DELETE = \033[2K\r

all: ${NAME}
	@echo "\033[1;32mSuccess\033[0m"

${NAME}: ${LIBFT} ${OBJS_DIR} ${OBJS}
	@printf "$(DELETE)\033[1;33m...Building\033[0m %-33s" "${NAME}"
	@${CC} ${CFLAGS} ${CFLAGS_NAME} ${HEADERS_DIR_FLAG} -o ${NAME} ${OBJS} ${LIBFT_FLAG} -lreadline
	@echo "${OK_PROMPT}"
	@#${MAKE} tags

bonus: ${NAME_BONUS}
	@echo "\033[1;32mSuccess\033[0m \033[1;35mbonus\033[0m"

${NAME_BONUS}: ${NAME}
	@printf "\033[1;33m...Building\033[0m %-33s" "${NAME_BONUS}"
	@cp ${NAME} ${NAME_BONUS}
	@echo "${OK_PROMPT} \033[1;35mbonus\033[0m"

${OBJS_DIR}:
	@printf "\033[1;34m...Creating\033[0m %-33s" "${OBJS_DIR} directory"
	@${MKDIR} ${OBJS_DIR}
	@${MKDIR} ${OBJS_DIR}/1-data ${OBJS_DIR}/2-builtin ${OBJS_DIR}/3-front ${OBJS_DIR}/4-back ${OBJS_DIR}/5-utils
	@printf "\033[1;32mdone\033[0m"

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@printf "$(DELETE)\033[1;34mCompiling\033[0m %-35s" $<
	@${CC} ${CFLAGS} ${HEADERS_DIR_FLAG} -c $< -o $@
	@printf "${OK_PROMPT}"

${OBJS_BONUS}: OK_PROMPT += \033[1;35mbonus\033[0m

${OBJS_DIR}/b_%.o: ${SRCS_DIR}/%.c
	@printf "\033[1;34mRecompiling\033[0m %-33s" $<
	@${CC} ${CFLAGS} ${HEADERS_DIR_FLAG} -D BONUS=1 -c $< -o $@
	@echo "${OK_PROMPT}"

${LIBFT}: force
	@${MAKE} -C ${LIBFT_DIR} ${LIBFT_TARGET}

norm:
	@printf "\n\033[1;33mChecking norm...\033[0m %-18s" " "
	@echo $$(a=$$(git ls-files | grep -E ".*\.[ch]$$" | grep -v "test" | \
	xargs -n 4 -P 4 norminette | grep --color=always Error) ; b=$$(printf "%s" "$$a" | wc -l) ; \
	if [ $$b -eq 0 ]; then ${ECHO} "\033[1;32mdone\033[0m" ; \
	else ${ECHO} "\033[1;31mERROR\033[0m" ; printf "%s\n" "$$a" ; fi ; ) | sed \
	"s/Error/\nError/Ig"

clean:
	@${MAKE} -C test fclean
	@${MAKE} -C ${LIBFT_DIR} clean
	@${RM} ${OBJS} ${OBJS_BONUS}
	@${RMDIR} ${OBJS_DIR}/1-data ${OBJS_DIR}/2-builtin ${OBJS_DIR}/3-front ${OBJS_DIR}/4-back ${OBJS_DIR}/5-utils ${OBJS_DIR}
	@printf "\033[1;34m%-44s\033[0m \033[1;32m%s\033[0m\n" "Cleaning" "done"

fclean: clean
	@${MAKE} -C test fclean
	@${MAKE} -C ${LIBFT_DIR} fclean
	@${RM} ${NAME} ${NAME_BONUS}
	@${RM} tags
	@printf "\033[1;34m%-44s\033[0m \033[1;32m%s\033[0m\n" "File cleaning" "done"

re: fclean all

debug: all

sanitize:
	@printf "\033[1;34m%-44s\033[0m \033[1;32m%s\033[0m\n" "Output is sanitized" "done"

tags:force
	@printf "\033[1;33m.Generating\033[0m %-33s" "tags"
	@ctags --options=.ctags
	@echo "\033[1;32mdone\033[0m"

force:;

# supprime les fichiers dupliqués sur mac
mac_clean:
	@find . -type f -name "* [2-9]*" -print -delete

meson/meson.py:
	git submodule init
	git submodule update

test/lib: meson/meson.py
	cd criterion ; python3 ../meson/meson.py setup --prefix=$$(realpath ../test) build ; cd build ; \
		python3 ../../meson/meson.py compile ; python3 ../../meson/meson.py test
	cd criterion ; python3 ../meson/meson.py install -C build

run_test: test/lib ${LIBFT} ${OBJS_DIR} ${OBJS}
	@${MAKE} -C test
	@#valgrind -q --leak-check=full --show-leak-kinds=all
	@if [ $$(echo $$LD_LIBRARY_PATH | grep -c "test") -eq 0 ]; \
		then export LD_LIBRARY_PATH=$$(realpath test/lib64):$$(realpath test/lib/x86_64-linux-gnu):$$LD_LIBRARY_PATH \
		; fi ; ./test.out --verbose 2>&1 ; exit 0
	@echo \'export LD_LIBRARY_PATH=$$(realpath test/lib64):$$(realpath test/lib/x86_64-linux-gnu):\$$LD_LIBRARY_PATH\' before running
testing: test/lib ${LIBFT} ${OBJS_DIR} ${OBJS}
	@${MAKE} -C test
	@echo \'export LD_LIBRARY_PATH=$$(realpath test/lib64):$$(realpath test/lib/x86_64-linux-gnu):\$$LD_LIBRARY_PATH\' before running
