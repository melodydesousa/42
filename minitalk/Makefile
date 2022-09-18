SRCS_LIBFT = ./libft/

SRCS_SERVER = server.c

SRCS_CLIENT = client.c

OBJS_SERVER	= ${SRCS_SERVER:.c=.o}
OBJS_CLIENT	= ${SRCS_CLIENT:.c=.o}
SERVER	= server
CLIENT	= client
CC	= gcc -g3
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -Iincludes -o ${<:.c=.o}

${SERVER}:	${OBJS_SERVER}
		$(MAKE) -C ${SRCS_LIBFT}
		${CC} ${CFLAGS} -o $@ $^ ${SRCS_LIBFT}libft.a 

${CLIENT}:	${OBJS_CLIENT}
		$(MAKE) -C ${SRCS_LIBFT}
		${CC} ${CFLAGS} -o $@ $^ ${SRCS_LIBFT}libft.a

all:	${SERVER} ${CLIENT}

clean:
		${RM} ${OBJS_SERVER} ${OBJS_CLIENT} 
		$(MAKE) -C ${SRCS_LIBFT} clean

fclean: clean
		${RM} ${SERVER} ${CLIENT}
		# $(MAKE) -C ${DIR_LIBFT} fclean
 
re: fclean
	make all

.PHONY: all clean fclean re
