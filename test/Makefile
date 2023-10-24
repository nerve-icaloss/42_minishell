NAME = ../test.out
CC = gcc -g
TO_NOT_GET = ../obj/main.o# ../obj/data/history.o ../obj/data/shell.o ../obj/history.o ../obj/parser.o ../obj/builtin/blt_exit.o ../obj/parser_utils.o # if wanna debug this, please fix all headers problem first AND please keep main.o in there
OBJ_UP = $(filter-out $(TO_NOT_GET), $(shell find ../obj/ -type f -name "*.o"))
OBJS_DIR = obj
SRCS = $(shell find . -type f -name "*.c")
OBJS = ${patsubst ./%.c,${OBJS_DIR}/%.o,$(SRCS)}
LIBRARIES = -L ./lib64 -L ./lib/x86_64-linux-gnu -lcriterion -L ../src/libft \
			-l:libft.a -L/usr/local/lib -I/usr/local/include -lreadline
INCLUDES = -I ../headers -I ../src/libft/ -I ./include -I ../src

#	${CC} -L . -lminishell ${HEADERS_DIR_FLAG} ${LIBRARY_SEARCH_PATH} \
#		${LIBRARY_TESTS} -o test.out ${LIBFT} $(filter-out obj/main.o , $(OBJS))
#./test.out
RM = rm -f
RMDIR = rm -df
MKDIR = mkdir

all: universal.h ${OBJS_DIR} ${OBJS}
	@${CC} ${INCLUDES} -no-pie -o ${NAME} ${OBJS} ${OBJ_UP} ../src/libft/libft.a ${LIBRARIES}

${OBJS_DIR}:
	@${MKDIR} ${OBJS_DIR}

${OBJS_DIR}/%.o: %.c
	@${CC} ${LIBRARIES} ${INCLUDES} ${CFLAGS} ${HEADERS_DIR_FLAG} -c $< -o $@

clean:
	@${RM} ${OBJS}
	@${RMDIR} ${OBJS_DIR}

fclean: clean
	@${RM} ${NAME}

re: fclean all

universal_clean:
	@rm -f universal.h

universal.h: universal_clean
	@find ../headers -type f -name "*.h" -exec echo "#include \"{}\"" \;  >> universal.h
	@find ../src -type f -name "*.h" -exec echo "#include \"{}\"" \;  >> universal.h
