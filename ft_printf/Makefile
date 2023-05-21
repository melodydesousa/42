SRCS	= ft_printf.c\
		ft_printf_utils.c\
		ft_printf_format.c

OBJS	= ${SRCS:.c=.o}
NAME	= libftprintf.a
CC	= gcc
AR	= ar rc
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -Iincludes -o ${<:.c=.o}

${NAME}:	${OBJS}
			${AR} ${NAME} ${OBJS}

all:	${NAME}

clean:	
		${RM} ${OBJS} ${OBJS_BONUS}

fclean:	clean
		${RM} ${NAME}

re:	fclean 
	make all

.PHONY: all clean fclean re
