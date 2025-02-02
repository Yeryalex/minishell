# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 17:31:12 by yrodrigu          #+#    #+#              #
#    Updated: 2025/02/02 14:17:57 by yrodrigu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

HEADER = inc/minishell.h 
LIBFT = inc/libft/libft.a
CFLAGS = -Wall -Werror -Wextra
#-g -fsanitize=address -fsanitize=leak

CFILES =	main.c \
			lexer/prompt.c \
			lexer/lexer_utils.c \
			parser/parser.c \
			parser/parser_utils.c \
			utils/init_env.c \
			utils/env_export.c \
			utils/free.c \
			utils/init_utils.c \
			utils/ft_get_value_from_env.c\
			expanser/expanser.c \
			expanser/split_path.c \
			expanser/utils_expanser.c \
			executor/ft_executor.c\
			builtins/echo.c\
			builtins/env.c\
			builtins/pwd.c\
			builtins/export.c\
			builtins/x_utils.c\
			builtins/x_utils2.c\
			builtins/unset.c\

GREEN = "\033[92m"
RESET = "\033[0m"


OBJS = $(addprefix src/, $(CFILES:.c=.o))

all: library $(NAME)

$(NAME): $(OBJS)
	@echo " "
	@echo $(GREEN)		Successfully compiled!$(RESET)
	@echo " "
	@$(CC) $(CFLAGS) -g $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c $(HEADER) Makefile
	@$(CC) $(CFLAGS) -g -c $< -o $@

library:
	@make -C inc/libft --silent

clean:
	@make clean -C inc/libft --silent
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C inc/libft --silent
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re library
