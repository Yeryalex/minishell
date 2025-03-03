# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/06 17:31:12 by yrodrigu          #+#    #+#              #
#    Updated: 2025/02/28 22:20:57 by rbuitrag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

HEADER = inc/minishell.h 
LIBFT = inc/libft/libft.a

CFLAGS = -Wall -Werror -Wextra  -g #-fsanitize=address -fsanitize=leak

CFILES =	main.c \
			lexer/prompt.c \
			lexer/lexer_utils.c \
			lexer/lexer.c \
			lexer/env_utils.c \
			lexer/init_lexer.c \
			lexer/read_input.c \
			lexer/lexer_get_values.c \
			lexer/quotes.c \
			lexer/quotes_utils.c \
			lexer/token_syntax.c \
			lexer/ft_norminette.c \
			parser/init_cmd.c \
			parser/parser.c \
			parser/parser_utils.c \
			parser/redir.c \
			parser/redir_utils.c \
			parser/hdoc.c \
			parser/hdoc_utils.c \
			parser/read.c \
			utils/init_env.c \
			utils/env_export.c \
			utils/free.c \
			utils/init_utils.c \
			utils/ft_get_value_from_env.c\
			utils/signals.c \
			utils/general_utils.c\
			utils/general_utils2.c\
			expanser/expanser.c \
			expanser/utils_expanser.c \
			expanser/expand_hdoc.c \
			expanser/search_expanser.c \
			executor/ft_executor.c\
			executor/executor_utils.c\
			builtins/echo.c\
			builtins/env.c\
			builtins/pwd.c\
			builtins/export.c\
			builtins/x_utils.c\
			builtins/x_utils2.c\
			builtins/x_utils3.c\
			builtins/unset.c\
			builtins/cd.c\
			builtins/exit.c\
			builtins/exit_utils.c\
			

GREEN = "\033[92m"
RESET = "\033[0m"


OBJS = $(addprefix src/, $(CFILES:.c=.o))

all: library $(NAME)

$(NAME): $(OBJS)
	@echo " "
	@echo $(GREEN)		Successfully compiled!$(RESET)
	@echo " "
	@$(CC) $(CFLAGS) -g $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c $(HEADER) Makefile $(LIBFT)
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

va: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.ignore -q -s ./minishell

valog: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --log-file=valgrind_output.log --suppressions=readline.ignore -q -s ./minishell

.PHONY: all clean fclean re library
