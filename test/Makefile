NAME = ../test.out
CC = gcc -g
OBJ_UP = $(filter-out ../obj/main.o, $(shell find ../obj/ -type f -name "*.o"))
OBJS_DIR = obj
SRCS = $(shell find . -type f -name "*.c")
OBJS = ${patsubst ./%.c,${OBJS_DIR}/%.o,$(SRCS)}
LIBRARIES = -L ./lib64 -L ./lib/x86_64-linux-gnu -lcriterion -L ../src/libft -l:libft.a
INCLUDES = -I ../headers -I ../src/libft/ -I ./include

#	${CC} -L . -lminishell ${HEADERS_DIR_FLAG} ${LIBRARY_SEARCH_PATH} \
#		${LIBRARY_TESTS} -o test.out ${LIBFT} $(filter-out obj/main.o , $(OBJS))
#./test.out
RM = rm -f
RMDIR = rm -df
MKDIR = mkdir

all: universal.h ${OBJS_DIR} ${OBJS}
	@${CC} ${LIBRARIES} ${INCLUDES} -o ${NAME} ${OBJS} ${OBJ_UP} ../src/libft/libft.a

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
	@find ../headers -type f -name "*.h" -exec cat {} >> universal.h \;
	@find ../src -type f -name "*.h" -exec cat {} >> universal.h \;
