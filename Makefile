NAME		:= miniRT

JOBS ?= $(shell nproc 2>/dev/null || echo 4)

SAMPLES ?= 2
CHECK ?= 1

CC		:= $(if $(shell command -v ccache 2>/dev/null),ccache cc,cc)
CFLAGS	:= -Wall -Wextra -Werror -I minilibx-linux -I. -g3 -O3 -D SAMPLES_NUMBER=$(SAMPLES) -D CHECK_BOARD=$(CHECK)
LDFLAGS = -L minilibx-linux -lmlx -lXext -lX11 -lm -lz

MLX = minilibx-linux/libmlx.a

INCLUDES	:= -I./includes -I./libft

LIBFT_DIR	:= ./libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRC_DIR		:= srcs

SRCS	:= \
	main.c \
	parse/parse.c \
	parse/parse_to_scene.c \
	parse/parse_scene.c \
	parse/parse_utils.c \
	parse/parse_utils2.c \
	parse/parse_objects.c \
	parse/parse_material.c \
	parse/scene_free.c \
	vec_utils/vec_ops1.c \
	vec_utils/vec_ops2.c \
	vec_utils/vec_ops3.c \
	objects/intersections.c \
	image/image.c \
	objects/cylinder.c \
	image/color_processing.c \
	vec_utils/samples.c \
	path_tracing/path_tracing.c \
	path_tracing/bdrf_utils.c \
	path_tracing/pt_utils.c \
	path_tracing/pt_sampling.c \
	path_tracing/pt_brdf.c \
	path_tracing/pt_pdf.c \
	path_tracing/pt_light.c

OBJS	:= $(addprefix $(SRC_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(MLX):
	@$(MAKE) -C minilibx-linux

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean
	$(MAKE) -j$(JOBS) all

.PHONY: all clean fclean re
