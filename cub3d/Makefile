# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRCS    =	parsing/cub3d.c\
	parsing/cub3d_utils.c\
	parsing/cub3d_utils_2.c\
	parsing/cub3d_check_errors.c\
	parsing/cub3d_check_errors2.c\
	parsing/cub3d_check_errors_map.c\
	parsing/cub3d_check_errors_map2.c\
	parsing/cub3d_make_tab.c\
	parsing/cub3d_make_colors.c\
	parsing/cub3d_init.c\
	parsing/cub3d_destroy.c\
	parsing/cub3d_make_path.c\
	parsing/cub3d_save_path.c\
	parsing/cub3d_remake_map.c\
	parsing/cub3d_remake_map2.c\
	ray-casting/init_minilibx_and_colors.c\
	ray-casting/handle_events.c\
	ray-casting/ray_casting_init.c\
	ray-casting/ray_casting.c\
	ray-casting/ray_casting_draw.c\
	ray-casting/ft_close_all.c

SRCS_BONUS	=	parsing/cub3d_bonus.c\
	parsing/cub3d_utils_bonus.c\
	parsing/cub3d_utils_2_bonus.c\
	parsing/cub3d_check_errors_bonus.c\
	parsing/cub3d_check_errors2_bonus.c\
	parsing/cub3d_check_errors_map_bonus.c\
	parsing/cub3d_check_errors_map2_bonus.c\
	parsing/cub3d_make_tab_bonus.c\
	parsing/cub3d_make_colors_bonus.c\
	parsing/cub3d_init_bonus.c\
	parsing/cub3d_destroy_bonus.c\
	parsing/cub3d_make_path_bonus.c\
	parsing/cub3d_save_path_bonus.c\
	parsing/cub3d_remake_map_bonus.c\
	parsing/cub3d_remake_map2_bonus.c\
	ray-casting/init_minilibx_and_colors_bonus.c\
	ray-casting/handle_events_bonus.c\
	ray-casting/ray_casting_init_bonus.c\
	ray-casting/ray_casting_bonus.c\
	ray-casting/ray_casting_draw_bonus.c\
	ray-casting/ft_close_all_bonus.c

DIR_SRC_CUB3D = ./sources/srcs_cub3d/
DIR_SRC_CUB3D_BONUS = ./sources_bonus/srcs_cub3d_bonus/

OBJ	= ${SRCS:.c=.o}
OBJ_BONUS = ${SRCS_BONUS:.c=.o}
DIR_OBJ = sources/objs/
DIR_OBJ_BONUS = sources_bonus/objs_bonus/
OBJS = $(addprefix $(DIR_OBJ), $(OBJ))
OBJS_BONUS = $(addprefix $(DIR_OBJ_BONUS), $(OBJ_BONUS))

DEP = ${SRCS:.c=.d}
DEP_BONUS = ${SRCS_BONUS:.c=.d}
DEPS = $(addprefix $(DIR_OBJ), $(DEP))
DEPS_BONUS = $(addprefix $(DIR_OBJ_BONUS), $(DEP_BONUS))

LMLX	= -L minilibx-linux -lmlx -lXext -lX11 -lm
NAME = cub3D
NAME_BONUS = cub3D_bonus

HEADERS	= -I includes minilibx-linux
CC		= gcc
CFLAGS	= -MMD -Wall -Wextra -Werror

${NAME} :	${OBJS}
			@make -C ./sources/libft
			@make -C minilibx-linux
			@echo "$(GRAY)cub3D compiled!$(DEF_COLOR)"
			@${CC} ${CFLAGS} ${OBJS} ./sources/libft/libft.a -o ${NAME} ${LMLX}

${NAME_BONUS} :	${OBJS_BONUS}
			@make -C ./sources_bonus/libft
			@make -C minilibx-linux
			@echo "$(BLUE)cub3D bonus compiled!$(DEF_COLOR)"
			@${CC} ${CFLAGS} ${OBJS_BONUS} ./sources_bonus/libft/libft.a -o ${NAME_BONUS} ${LMLX}

all :		cub3D cub3D_bonus

bonus :		cub3D_bonus

clean:
			@rm -f ${OBJS} ${DEPS} 
			@echo "$(GRAY)cub3D cleaned$(DEF_COLOR)"
			@rm -f ${OBJS_BONUS} ${DEPS_BONUS}
			@echo "$(BLUE)cub3D bonus cleaned$(DEF_COLOR)"

fclean:		clean
			@make -C ./sources/libft fclean
			@make -C ./sources_bonus/libft fclean
			@make -C minilibx-linux clean
			@rm -f cub3D
			@rm -f cub3D_bonus

re:			fclean 
			make all

$(DIR_OBJ)%.o: $(DIR_SRC_CUB3D)%.c
	@echo "$(GRAY)Compiling: $< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -c -Iincludes $< -o $@

$(DIR_OBJ_BONUS)%.o: $(DIR_SRC_CUB3D_BONUS)%.c
	@echo "$(BLUE)Compiling: $< $(DEF_COLOR)"
	@${CC} ${CFLAGS} -c -Iincludes $< -o $@

-include ${DEPS}

.PHONY: all clean fclean re