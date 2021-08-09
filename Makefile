SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
    components/map_validator/parse_config_str.c \
    components/map_validator/read_line.c \
    components/map_validator/error_config.c \
    components/map_validator/create_map.c \
    components/map_validator/ch_map.c \
    components/map_validator/config_is_init.c \
    components/engine/raycast.c \
    components/engine/set_direction.c \
    components/engine/clear.c \
    components/engine/exit_with_error.c \
    components/engine/init_game.c \
    components/engine/movement.c \
    components/engine/create_rgb.c \
    components/engine/events_key.c \
    components/engine/utils.c \
    components/engine/check_file_ext.c \
    components/engine/append_map_line.c \
    main.c
OBJS = $(SRCS:.c=.o)

MAKE = make

CC				= gcc
RM				= rm -f
#CFLAGS			= -Wall -Wextra -Werror -I.
CFLAGS			= 

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS		= -L . -lmlx -lft -lXext -lX11 -lm -lz
	MLX		= libmlx.a
	MLX_DIR		= minilibx-linux
else
	LIBS		= -L . -lmlx -lft -framework OpenGL -framework AppKit -lm
	MLX		= libmlx.dylib
	MLX_DIR		= minilibx-linux
endif

LFT			= libft.a

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(LFT) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
				@$(MAKE) -C $(MLX_DIR)
#				@$(MAKE) -C minilibx
#				@mv minilibx/$(MLX) .
				@mv $(MLX_DIR)/$(MLX) .

$(LFT):
				@$(MAKE) -C libft
				@mv libft/$(LFT) .

clean:
				@$(MAKE) -C $(MLX_DIR) clean
				@$(MAKE) -C libft clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX) $(LFT)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
