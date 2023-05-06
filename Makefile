CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
LIBFT = libft.a
LIBFT_DIR = ./libft
INCLUDES = -I$(LIBFT_DIR)
		
SRC_PATH = ./src/
SRCS = $(SRC_PATH)utils.c $(SRC_PATH)main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

