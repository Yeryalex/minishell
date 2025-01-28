/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:32:28 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/28 20:04:25 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
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
	H_DOC, // << HEREDOC
	APPEND, // >> 
	WORD,
}	t_type;

typedef struct s_tokens
{
	char			*value;
	t_type			token;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}	t_tokens;

typedef struct s_dir
{
	int		heredoc;
	int		fd;
	char	*filename;

}	t_dir;

typedef struct s_cmds
{
	char			**cmd_array;
	char			*full_path;
	t_dir			*redir_in;
	t_dir			*redir_out;
	struct s_cmds 	*next;
	struct s_cmds	*prev;
} t_cmds;

typedef struct s_env
{
	int				exported;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_utils
{
	t_env 			*environ;
	int				stdin;
	int				stdout;
	char			*builtins[8];
	struct s_utils	*next;
	struct s_utils	*prev;
}	t_utils;

/*          MAIN FUNCTIONS         */
void    prompt_loop(t_utils *utils, char *path);

/*          LEXER FUNCTIONS         */
t_type		ft_determine_type(char *value);
t_tokens	*ft_create_node(const char **value);
t_tokens	*ft_lexer_input(const char *input);
char		*read_input(void);
int			ft_addlast_node(t_tokens **lexer, t_tokens *current_node);
char		*ft_get_word(const char **line);
char		*ft_get_value(const char **line);

/*			PARSER FUNCTIONS		*/
t_cmds	*ft_parser(t_tokens *lexer, char *path);
t_cmds	*ft_create_node_cmd(t_tokens *lexer, int count, char *cmd_path);
void    ft_addlast_pnode(t_cmds **list, t_cmds *node);


/*          STRUCT FUNCTIONS         */

/*          REDIR FUNCTIONS         */

/*          BUILTINS FUNCTION:S         */
int		ft_echo(char **cmd, int fd);
int		ft_env(t_utils *utils, int fd);
int		ft_pwd(t_env *env);
int		ft_export(t_cmds *cmd, t_env *env);

/*          SIGNAL FUNCTIONS         */

/*          ENV FUNCTIONS         */
t_env		*ft_init_env(char **env);
t_env		*ft_create_node_env(char *env);
int			ft_clear_lstenv(t_env *env);
void    	ft_add_env_tolst(t_env **lst_env, t_env *new_node);
char		*ft_get_env_value(char *key_value);
char		*ft_get_env_key(char *str);
char		*ft_get_paths_from_env(t_env *environ);


/*          EXPORT FUNCTIONS         */
void		*ft_print_stderr(char *str);
//int			ft_print_env(t_env *env_list, int fd);
void 		ft_print_env_list(t_env *env);

/*          EXPAND FUNCTIONS         */
t_cmds *ft_expand_tokens(t_tokens *tokens, t_env *env);
char **ft_split_path(const char *path);
char *ft_validate_command(char **paths, const char *command);
void execute_commands(t_cmds *cmd, char **env);
char    *ft_get_path(char *path, char *cmd);


/*          EXECUTOR FUNCTIONS         */
void	ft_executor(t_cmds *cmd, t_utils *utils, char **env);
/*          AUXILIARS FUNCTIONS         */
int		ft_isspace(char c);
void	*ft_exit_error(char quote);
int		ft_is_metacharacter(int c);

/* UTILS FUNCTIONS */

void	init_utils(t_utils *utils, t_env *env);
char	*get_value_from_env(t_env *env, char *key);
/*          FREE FUNCTIONS         */
void	ft_free_tokens(t_tokens **lexer);
void    ft_free_cmd(t_cmds *cmd);
void    *ft_free_one_to_cmd(t_cmds *cmd);
void    *ft_free_redir(t_dir *node);
void	ft_free_array(char **array);

#endif
