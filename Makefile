NAME	:= minishell
CC		:= cc
CFLAGS	:= -I src/ -I lib/ -g3 #-fsanitize=address #-Wall -Werror -Wextra
LDFLAGS	:=
VPATH	:= src/ src/parsing/ src/env/
OBJ_DIR	:= obj/


SRC		:=	main.c\
			parsing.c\
			#tokens.c\

OBJ		:= $(addprefix $(OBJ_DIR), $(patsubst %.c, %.o, $(SRC)))

LIBFT	:= libft

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR): 
	mkdir obj

$(OBJ_DIR)%.o: %.c 
	$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT):
	make -C ./libft

clean:
	make -C ./libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, libft
