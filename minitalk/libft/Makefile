SRCS	= ft_strlcat.c\
		ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_str_is_numeric.c\
		ft_isprint.c\
		ft_iterative_power.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putstr.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\
		printf/ft_printf_format.c\
		printf/ft_printf_utils.c\
		printf/ft_printf.c\
		get_next_line/get_next_line.c\
		get_next_line/get_next_line_utils.c

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a
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

bonus:	 ${OBJS} ${OBJS_BONUS}
			${AR} ${NAME} ${OBJS} ${OBJS_BONUS}

.PHONY: all clean fclean re bonus
