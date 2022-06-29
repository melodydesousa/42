SRCS	= ft_split.c\
		push_swap.c\
		utils_init_a.c\
		operation_swap.c\
		operation_push.c\
		operation_rotate.c\
		operation_reverse.c
		
OBJS	= ${SRCS:.c=.o}
NAME	= push_swap
CC	= gcc
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -Iincludes -o ${<:.c=.o}

${NAME}:	${OBJS}
		${CC} ${CFLAGS} -o $@ $^

all:	${NAME}

clean:
		${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
		${RM} ${NAME}
 
re: fclean
	make all

.PHONY: all clean fclean re
