SRCS = main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)

MAKE = make

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.

LIBS = -L . -lmlx -lft -framework OpenGL -framework AppKit -lm

LFT             = libft.a
MLX				= libmlx.dylib

NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(LFT) $(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

$(MLX):
				@$(MAKE) -C minilibx
				@mv minilibx/$(MLX) .

$(LFT):
				@$(MAKE) -C libft
				@mv libft/$(LFT) .

clean:
				@$(MAKE) -C minilibx clean
				@$(MAKE) -C libft clean
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) $(MLX) $(LFT)

re:				fclean $(NAME)

.PHONY:			all clean fclean re