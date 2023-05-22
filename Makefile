# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 15:35:55 by lahamoun          #+#    #+#              #
#    Updated: 2023/05/22 15:36:36 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell

LIBFT = libft.a
LIBFT_DIR = ./libft

INCLUDES = -I$(LIBFT_DIR)
SRC_DIR = ./src/
OBJ_DIR = ./obj/

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

SRCS = $(wildcard $(SRC_DIR)*.c)
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

-include $(DEPS)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)Linking...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)Done!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@echo "$(RED)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "$(RED)Cleaning up...$(NC)"
	rm -f $(OBJS) $(DEPS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re


# CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# NAME = minishell
# LIBFT = libft.a
# LIBFT_DIR = ./libft
# INCLUDES = -I$(LIBFT_DIR)

# SRC_PATH = ./src/
# SRCS = $(SRC_PATH)utils.c $(SRC_PATH)main.c $(SRC_PATH)parse_input.c $(SRC_PATH)parse_cmd_line.c\
# $(SRC_PATH)utils02.c $(SRC_PATH)parse_op_spaces.c
# OBJS = $(SRCS:.c=.o)

# all: $(NAME)

# $(NAME): $(LIBFT) $(OBJS)
# 	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT_DIR)/$(LIBFT) -lreadline -o $(NAME)

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_DIR)

# %.o: %.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# clean:
# 	rm -f $(OBJS)
# 	$(MAKE) clean -C $(LIBFT_DIR)

# fclean: clean
# 	rm -f $(NAME)
# 	$(MAKE) fclean -C $(LIBFT_DIR)

# re: fclean all

# .PHONY: all clean fclean re

