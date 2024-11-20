# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 17:31:12 by yrodrigu          #+#    #+#              #
#    Updated: 2024/11/20 13:07:05 by rbuitrag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

HEADER = inc/minishell.h 
LIBFT = libft/libft.a
CFLAGS = -Wall -Werror -Wextra
CC = gcc

CFILES =	main.c \
		minishell.c	



OBJS = $(addprefix src/, $(CFILES:.c=.o))

all: library $(NAME) Makefile

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lm -lz -o $(NAME)

%.o: %.c $(HEADER) 
	@$(CC) $(CFLAGS) -O3 -c $< -o $@

library:
	@make -C libft

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re library
