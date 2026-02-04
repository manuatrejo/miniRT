NAME		:= miniRT

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -I minilibx-linux -I. -g3
LDFLAGS = -L minilibx-linux -lmlx -lXext -lX11 -lm -lz

MLX = minilibx-linux/libmlx.a

INCLUDES	:= -I./includes -I./libft

LIBFT_DIR	:= ./libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS	:= \
	srcs/main.c \
	srcs/parse/parse.c \
	srcs/parse/parse_to_scene.c \
	srcs/parse/parse_scene.c \
	srcs/parse/parse_utils.c \
	srcs/parse/parse_utils2.c \
	srcs/parse/parse_objects.c \
	srcs/parse/parse_material.c \
	srcs/parse/scene_free.c \
	srcs/vec_ops/vec_ops1.c \
	srcs/vec_ops/vec_ops2.c \
	srcs/vec_ops/vec_ops3.c \
	srcs/rays/intersections.c \
	srcs/image/image.c \
	srcs/rays/cylinder.c \
	srcs/image/color_processing.c \
	srcs/image/ilumination.c

OBJS	:= $(SRCS:.c=.o)

all: $(NAME) $(MLX)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(MLX):
	@make -C minilibx-linux

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run:
	@make all -s
	@./miniRT algo.rt

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re