SRCS = main.c
OBJS = $(SRCS:.c=.o)

MAKE = make

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

LIBS = -L . -lmlx -framework OpenGL -framework AppKit -lm

MLX				= libmlx.dylib

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
				@$(MAKE) -C minilibx
				@mv minilibx/$(MLX) .

clean:
				@$(MAKE) -C minilibx clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re