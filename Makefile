SRCS_LIBFT = ./libft/

SRCS = so_long.c\
	init_map.c\
	init_struct.c\
	check_errors.c\
	handle_events.c\
	ft_close.c

OBJS = ${SRCS:.c=.o}
NAME = so_long
CC	= gcc -g
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c -Iincludes $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		$(MAKE) -C ${SRCS_LIBFT}
		$(CC) ${CFLAGS} -o $@ $^ ${SRCS_LIBFT}libft.a -L mlx_linux/ -lmlx -lXext -lX11

all:	${NAME} 

clean:
		${RM} ${OBJS}
		$(MAKE) -C ${SRCS_LIBFT} clean

fclean: clean
		${RM} ${NAME}
		$(MAKE) -C ${SRCS_LIBFT} fclean
 
re: fclean
	make all

.PHONY: all clean fclean re
