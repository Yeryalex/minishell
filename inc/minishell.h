/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:32:28 by yrodrigu          #+#    #+#             */
/*   Updated: 2024/11/28 16:40:42 by rbuitrag         ###   ########.fr       */
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
# define RESET "\033[0m"

typedef enum e_type
{
	NONE,
	PIPE,  // |
	GTHAN, // >
	STHAN, // <
	H_DOC, // HEREDOC
	APPEND, 
	WORD,
}	t_type;

typedef struct s_tokens
{
	char			*value;
	t_type			token;
	struct s_tokens	*next;
}	t_tokens;

/*          MAIN FUNCTIONS         */
void    prompt_loop(void);

/*          LEXER FUNCTIONS         */
t_type		ft_determine_type(char *value);
t_tokens	*ft_create_node(const char **value);
t_tokens	*ft_lexer_input(const char *input);
char		*read_input(void);
int			ft_addlast_node(t_tokens **lexer, t_tokens *current_node);
char		*ft_get_word(char **line);
char		*ft_get_value(char **line)




/*          STRUCT FUNCTIONS         */

/*          REDIR FUNCTIONS         */

/*          BUILTINS FUNCTIONS         */

/*          SIGNAL FUNCTIONS         */

/*          ENV FUNCTIONS         */

/*          EXPORT FUNCTIONS         */

/*          EXPAND FUNCTIONS         */

/*          EXECUTOR FUNCTIONS         */

/*          AUXILIARS FUNCTIONS         */
int		ft_isspace(char c);
void	*ft_exit_error(char quote);
int		ft_is_metacharacter(int c);

/*          FREE FUNCTIONS         */
void	ft_free_tokens(t_tokens **lexer);

#endif
