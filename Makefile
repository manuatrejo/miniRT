NAME		:= miniRT

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g -fsanitize=address

INCLUDES	:= -I./includes -I./libft

LIBFT_DIR	:= ./libft
LIBFT		:= $(LIBFT_DIR)/libft.a

SRCS	:= \
	srcs/main.c \
	srcs/parse/parse.c \
	srcs/parse/parse_scene.c \
	srcs/parse/parse_utils.c \
	srcs/parse/parse_utils2.c \
	srcs/parse/parse_objects.c \
	srcs/parse/scene_free.c \
	srcs/vec_ops/vec_ops1.c \
	srcs/vec_ops/vec_ops2.c

OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re