SRCS = so_long.c

OBJS = ${SRCS:.c=.o}
NAME = so_long
CC	= gcc -g
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c -Imlx $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		$(CC) ${CFLAGS} -o $@ $^ -L mlx_linux/ -lmlx -lXext -lX11 -framework OpenGL -framework AppKit -o $(NAME)
		# $(CC) $(OBJS) -Lmlx_linux -lmlx -framework OpenGL -framework AppKit -o $(NAME)


all:	${NAME} 

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}
 
re: fclean
	make all

.PHONY: all clean fclean re
