SRCS_LIBFT = ./libft/

SRCS_SERVER = server.c\
		server_utils.c

SRCS_CLIENT = client.c

OBJS_SERVER	= ${SRCS_SERVER:.c=.o}
OBJS_CLIENT	= ${SRCS_CLIENT:.c=.o}
SERVER	= server
CLIENT	= client
CC	= gcc 
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror -g3

.c.o:
		${CC} ${CFLAGS} -c $< -Iincludes -o ${<:.c=.o}

all:	${SERVER} ${CLIENT}

${SERVER}:	${OBJS_SERVER}
		make -C ${SRCS_LIBFT}
		${CC} ${CFLAGS} -o $@ $^ ${SRCS_LIBFT}libft.a

${CLIENT}:	${OBJS_CLIENT}
		make -C ${SRCS_LIBFT}
		${CC} ${CFLAGS} -o $@ $^ ${SRCS_LIBFT}libft.a

clean:
		${RM} ${OBJS_SERVER} ${OBJS_CLIENT}
		make -C ${SRCS_LIBFT} clean

fclean: clean
		${RM} ${SERVER} ${CLIENT}
 
re: fclean
	make all

.PHONY: all clean fclean re
