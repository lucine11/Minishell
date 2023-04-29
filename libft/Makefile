# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/22 10:58:32 by lahamoun          #+#    #+#              #
#    Updated: 2022/11/09 05:28:37 by lahamoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

FILES=	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_striteri.c \
	
BSRCS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		
NAME	= libft.a

OFILES	= $(FILES:.c=.o)

OBONUS	= $(BSRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OFILES)

bonus: $(OFILES) $(OBONUS)

$(OBONUS):$(BSRCS)
	$(CC) $(CFLAGS) -c $(BSRCS)
	ar -rc $(NAME) $(OBONUS)

$(OFILES):$(FILES)
	$(CC) $(CFLAGS) -c $(FILES)
	ar -rc $(NAME) $(OFILES)

clean:
	rm -rf $(OFILES)  $(OBONUS)
fclean: clean
	rm -rf $(NAME)
re: fclean all
