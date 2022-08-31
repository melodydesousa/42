LIBFT = ./libft/

MLX = ./minilibx-linux/ 

SRCS = ./solong/main.c\
	./solong/init_map.c\
	./solong/init_values_img.c\
	./solong/check_errors.c\
	./solong/check_errors2.c\
	./solong/handle_events.c\
	./solong/ft_close.c\
	./solong/way_possible.c

SRCS_BONUS = ./solong_bonus/main_bonus.c\
	./solong_bonus/init_map_bonus.c\
	./solong_bonus/init_values_img_bonus.c\
	./solong_bonus/check_errors_bonus.c\
	./solong_bonus/check_errors2_bonus.c\
	./solong_bonus/handle_events_bonus.c\
	./solong_bonus/ft_close_bonus.c

OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
NAME = so_long
NAME_BONUS = bonus
CC	= gcc -g
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c -Iincludes $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		$(MAKE) -C ${LIBFT}
		$(MAKE) -C ${MLX}
		$(CC) ${CFLAGS} -o $@ $^ ${LIBFT}libft.a -L minilibx-linux/ -lmlx -lXext -lX11

${NAME_BONUS}: ${OBJS_BONUS}
		$(MAKE) -C ${LIBFT}
		$(MAKE) -C ${MLX}
		$(CC) ${CFLAGS} -o $@ $^ ${LIBFT}libft.a -L minilibx-linux/ -lmlx -lXext -lX11

all:	${NAME} ${NAME_BONUS}

clean:
		${RM} ${OBJS} ${OBJS_BONUS}
		$(MAKE) -C ${LIBFT} clean
		$(MAKE) -C ${MLX} clean

fclean: clean
		${RM} ${NAME} ${NAME_BONUS}
		$(MAKE) -C ${LIBFT} fclean
		$(MAKE) -C ${MLX} clean
 
re: fclean
	make all

.PHONY: all clean fclean re
