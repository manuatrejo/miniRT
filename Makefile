NAME		:= miniRT

JOBS ?= $(shell nproc 2>/dev/null || echo 4)

SAMPLES ?= 50

CC		:= $(if $(shell command -v ccache 2>/dev/null),ccache cc,cc)
CFLAGS	:= -Wall -Wextra -Werror -I minilibx-linux -I. -g3 -O3 -D SAMPLES_NUMBER=$(SAMPLES)
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
	srcs/image/ilumination.c \
	srcs/image/samples.c \
	srcs/image/path_tracing.c

OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -j -C $(LIBFT_DIR)


$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(MLX):
	@$(MAKE) -C minilibx-linux

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run:
	@$(MAKE) all -s -j$(JOBS)
	@./miniRT algo.rt

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all -j

r: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

.PHONY: all clean fclean re