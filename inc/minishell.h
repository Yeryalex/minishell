/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:32:28 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/11/26 16:28:34 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../inc/libft/libft.h"

# define CYAN "\033[96m"
# define GREEN "\033[92m"
# define YELLOW "\033[93m"
# define MAGENTA "\033[95m"
# define RED "\033[31m"
# define BLUE "\033[94m"
# define GRAY "\033[90m"

// Definimos una lista para tipo de palabra y luego controlarla (provisional)
typedef enum e_type
{
	PIPE,  // |
	GTHAN, // >
	STHAN, // <
	H_DOC, // HEREDOC
	APPEND, 
	WORD,
}	t_type;

// En la siguiente estructura deberemos guardar su tipo para trabajar con ellas después
typedef struct s_tokens
{
	char			*value;
	t_type			token;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}	t_tokens;



/*          MAIN FUNCTIONS         */
void    prompt_loop(void);

/*          LEXER FUNCTIONS         */
void		add_token(t_tokens **head, t_tokens *new_token);
t_type		determine_type(char c);
t_tokens	*create_token(const char *value, t_type type);
t_tokens	**parse_input(const char *input);
char		*read_input(void);




/*          STRUCT FUNCTIONS         */

/*          REDIR FUNCTIONS         */

/*          BUILTINS FUNCTIONS         */

/*          SIGNAL FUNCTIONS         */

/*          ENV FUNCTIONS         */

/*          EXPORT FUNCTIONS         */

/*          EXPAND FUNCTIONS         */

/*          EXECUTOR FUNCTIONS         */

/*          AUXILIARS FUNCTIONS         */
char	*ft_strndup(const char *s, size_t n);
int		ft_istoken(char c);
int		ft_ispace(char c);

/*          FREE FUNCTIONS         */
void	free_tokens(t_tokens *head);

#endif
