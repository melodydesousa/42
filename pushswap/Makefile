SRCS	= ft_split.c\
		push_swap.c\
		utils_init_a.c\
		utils_lst.c\
		utils_lst2.c\
		operations/operation_swap.c\
		operations/operation_push.c\
		operations/operation_rotate.c\
		operations/operation_reverse.c\
		utils_algo.c
		
OBJS	= ${SRCS:.c=.o}
NAME	= push_swap
CC	= gcc -g3
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
