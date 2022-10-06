SRCS = main.c\
	utils.c

OBJS = ${SRCS:.c=.o}
NAME = philo
CC	= gcc -pthread
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} -c $< -Iincludes -o ${<:.c=.o}

all:	${NAME} 

${NAME}:	${OBJS}
		${CC} ${CFLAGS} -o $@ $^

clean:
		${RM} ${OBJS} 

fclean: clean
		${RM} ${NAME}
 
re: fclean
	make all

.PHONY: all clean fclean re
