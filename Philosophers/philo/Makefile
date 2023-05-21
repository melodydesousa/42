SRCS = philo_main.c\
	philo_init.c\
	philo_utils.c\
	philo_eat.c\
	philo_eat_sleep_think.c\
	philo_death.c

OBJS = ${SRCS:.c=.o}
NAME = philo
CC	= gcc -pthread
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror -g

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
