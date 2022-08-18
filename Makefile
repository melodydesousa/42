SRCS_LIBFT	= libft/ft_strlcat.c\
			libft/ft_atoi.c\
			libft/ft_bzero.c\
			libft/ft_calloc.c\
			libft/ft_isalnum.c\
			libft/ft_isalpha.c\
			libft/ft_isascii.c\
			libft/ft_isdigit.c\
			libft/ft_isprint.c\
			libft/ft_memchr.c\
			libft/ft_memcmp.c\
			libft/ft_memcmp.c\
			libft/ft_memcpy.c\
			libft/ft_memmove.c\
			libft/ft_memset.c\
			libft/ft_strchr.c\
			libft/ft_strdup.c\
			libft/ft_strlcpy.c\
			libft/ft_strlen.c\
			libft/ft_strncmp.c\
			libft/ft_strnstr.c\
			libft/ft_strrchr.c\
			libft/ft_tolower.c\
			libft/ft_toupper.c\
			libft/ft_substr.c\
			libft/ft_strjoin.c\
			libft/ft_strtrim.c\
			libft/ft_split.c\
			libft/ft_itoa.c\
 			libft/ft_strmapi.c\
			libft/ft_striteri.c\
			libft/ft_putchar_fd.c\
			libft/ft_putstr_fd.c\
 			libft/ft_putendl_fd.c\
			libft/ft_putnbr_fd.c\
			libft/ft_lstnew.c\
			libft/ft_lstadd_front.c\
			libft/ft_lstsize.c\
			libft/ft_lstlast.c\
			libft/ft_lstadd_back.c\
			libft/ft_lstdelone.c\
			libft/ft_lstclear.c\
			libft/ft_lstiter.c\
			libft/ft_lstmap.c\
			libft/printf/ft_printf_format.c\
			libft/printf/ft_printf_utils.c\
			libft/printf/ft_printf.c\
			libft/get_next_line/get_next_line.c\
			libft/get_next_line/get_next_line_utils.c

SRCS_SERVER = server.c

SRCS_CLIENT = client.c

OBJS_LIBFT = ${SRCS_LIBFT:.c=.o}
OBJS_SERVER	= ${SRCS_SERVER:.c=.o}
OBJS_CLIENT	= ${SRCS_CLIENT:.c=.o}
SERVER	= server
CLIENT	= client
CC	= gcc 
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -Iincludes -o ${<:.c=.o}

${SERVER}:	${OBJS_SERVER} ${OBJS_LIBFT}
		${CC} ${CFLAGS} -o $@ $^

${CLIENT}:	${OBJS_CLIENT} ${OBJS_LIBFT}
		${CC} ${CFLAGS} -o $@ $^

all:	${SERVER} ${CLIENT}

clean:
		${RM} ${OBJS_SERVER} ${OBJS_CLIENT} ${OBJS_LIBFT}

fclean: clean
		${RM} ${SERVER} ${CLIENT}
 
re: fclean
	make all

.PHONY: all clean fclean re