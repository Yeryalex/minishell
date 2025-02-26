/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:32:28 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/26 18:22:07 by rbuitrag         ###   ########.fr       */
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
# include <errno.h>
# include <fcntl.h>
# include "../inc/libft/libft.h"

# define DEFAULT_ENV "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define CYAN "\033[96m"
# define GREEN "\033[92m"
# define YELLOW "\033[93m"
# define MAGENTA "\033[95m"
# define RED "\033[31m"
# define BLUE "\033[94m"
# define GRAY "\033[90m"
# define RESET "\033[0m"

extern int g_signal;

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
	int				error_fd;
	struct s_cmds 	*next;
	struct s_cmds	*prev;
} t_cmds;

typedef struct s_env
{
	int				exported;
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_utils
{
	t_env 			*environ;
	int				stdin;
	int				stdout;
	int				status;
	int				exit_status;
	int				cmds_amount;
	int				redir_error;
	char			*builtins[8];
	char			*value_to_expand;
	char			*temp_str;
	char			**env_in_char;
	struct s_utils	*next;
	struct s_utils	*prev;
}	t_utils;

typedef struct s_expand
{
	char			*old_value;
	char			*new_value;
	struct s_expand	*next;
}	t_exp;

/*          MAIN FUNCTIONS         */
void    prompt_loop(t_utils *utils);

/*          LEXER FUNCTIONS         */
t_type		ft_determine_type(char *value);
t_tokens	*ft_create_node(const char **value, t_utils *utils, t_tokens *lexer);
t_tokens	*ft_lexer_input(const char *input, t_utils *utils);
char		*read_input(char **env, t_utils *utils);
int			ft_addlast_node(t_tokens **lexer, t_tokens *current_node);
char		*ft_get_word(const char **line);
char		*ft_get_value(const char **line);
t_tokens	*ft_init_node(void);


/*			PARSER FUNCTIONS		*/
t_cmds *ft_parser(t_tokens *lexer, char *path, t_utils *utils);
t_cmds	*ft_create_node_cmd(t_tokens *lexer, int count, char *cmd_path, t_utils *utils);
void    ft_addlast_pnode(t_cmds **list, t_cmds *node);
void	*free_cmd_array(char **cmd_array);

/*          STRUCT FUNCTIONS         */

/*          REDIR FUNCTIONS         */
t_dir	*ft_append_gthan_redir(char *file_name, int token, t_utils *utils, t_cmds *parser_nodes);
t_dir	*ft_sthan_redir(char *file_name, t_utils *utils, t_cmds *parser_nodes);
t_dir	*ft_hdoc_redir(t_tokens **lexer_nodes, t_cmds *parser_nodes, t_utils *utils);
void	*ft_exit_redir(int error, t_dir *redir_node, t_utils *utils);
void	ft_child_hdoc(t_tokens **lexer_nodes, t_cmds *parser_nodes, t_dir *redir_node, t_utils *utils);
//void	ft_free_child_hdoc(t_tokens **lexer, t_cmds *cmds, t_utils *utils);
void	*ft_hdoc_error_handler(t_dir *redir_node, t_cmds *parser_nodes);
int		ft_gthan_append_cmds(t_tokens **lexer, t_cmds *cmds, t_utils *utils);
int		ft_sthan_hdoc_cmds(t_tokens **lexer, t_cmds *cmds, t_utils *utils);
int		ft_fork_hdoc(t_tokens **lexer_nodes, t_cmds *parser_nodes, t_dir *redir_node, t_utils *utils);
int		ft_open_fd(char *filename, int mode);
int		ft_read_to_file(char *stop, int cmds_amount, char *f_name);


/*          BUILTINS FUNCTION:S         */
int		ft_echo(char **cmd, int fd);
int		ft_env(t_utils *utils, int fd);
int		ft_pwd(t_env *env, int fd);
int		ft_export(t_cmds *cmd, t_env *env, int fd);
int		ft_unset(char **cmd_array, t_env  **env, int fd);
int		ft_cd(char **cmd_array, t_env *env);
int		ft_exit(char **cmd_array, t_utils *utils, int fd);

/*          SIGNAL FUNCTIONS         */
void		ft_init_signals(int child);
void		ft_control_c(t_utils *utils);
void		*handle_error_ctrl_d(char *stop, int cmd_num);

/*          ENV FUNCTIONS         */
t_env		*ft_init_env(char **env);
t_env		*ft_create_node_env(char *env);
int			ft_clear_lstenv(t_env *env);
void    	ft_add_env_tolst(t_env **lst_env, t_env *new_node);
char		*ft_get_env_value(char *key_value);
char		*ft_get_env_key(char *str);
char		*ft_get_paths_from_env(t_env *environ);
char		**ft_list_to_char(t_env *env);


/*          EXPORT FUNCTIONS         */
void	*ft_print_stderr(char *str);
//int			ft_print_env(t_env *env_list, int fd);
void 	ft_print_env_list(t_env *env);
void	ft_check_identifier(char **cmd_array, int *i, int *exit_status);
void	ft_trim_case(char **x_value);
int		ft_init_key_value(char **cmd_array, char **x_key, char **x_value, int *i);
void	ft_create_new_node(char **x_key, char **x_value, t_env *env);
t_env   *ft_add_node_env(char **cmd_array, t_env *env, int *exit_status);
int		ft_strcmp(char *s1, char *s2);
void	ft_sort_env(t_env *env);
t_env	*ft_find_key_env(t_env *env, char *key_value);
int		ft_abletojoin(char *str);
int		ft_key_end(char *str);
void    ft_flag_case1(t_env *node_already_exist, char **x_value);

/*          EXPAND FUNCTIONS         */
void	ft_expansion(int *i, int *j, t_utils *utils);
void	ft_start_expansion(t_utils *utils, char *temp_str, int *i, int *j);
void	ft_expand_variable(t_utils *utils, char *value_to_expand, char *temp_str, int *j);
void	ft_create_expansion(t_utils *utils, char *value_to_expand, int *i);
void	ft_apply_status(char *temp_str, int *j, t_utils *utils, int *i);
void    ft_assign_status(char *temp_str, int *j, t_utils *utils);
void	ft_expander_special(t_utils *utils, int *i, int *j, char *value_to_expand);
int		ft_check_special_char(char *str_value, int *i);
//void	ft_expanser(char **cmd, t_utils *utils);
//t_cmds *ft_expand_tokens(t_tokens *tokens, t_env *env);
//char **ft_split_path(const char *path);
//char *ft_validate_command(char **paths, const char *command);
//void execute_commands(t_cmds *cmd, char **env);

void	ft_exp_hd(t_dir *redir_node, t_utils *utils);
int		ft_valid_export(char *str);


/*          EXECUTOR FUNCTIONS         */
void	ft_executor(t_cmds *cmd, t_utils *utils, char **env);
void	ft_dup_close(t_cmds *cmd, int prev_read, int *fd);
void	ft_reset_read_end(t_cmds *current, int *prev_read, int *fd);
 void    ft_exec_builtin(t_cmds *cmd, t_utils *utils, int fd);
int		ft_is_builtin(t_cmds *cmd, t_utils *utils);
void	ft_call_builtin(t_cmds *cmd, t_utils *utils, int pipe);

void	ft_wait_for_children(int i, int *exit_status);

/*          AUXILIARS FUNCTIONS         */
int		ft_isspace(char c);
void	*ft_exit_error(char quote);
int		ft_is_metacharacter(int c);
void	ft_skip_spaces_and_quotes(char **input);
char	*ft_remove_quotes(char *value);
char 	*ft_strip_outer_quotes(char *value);
int		ft_is_enclosed_by_single_quotes(const char *value);
int		ft_count_double_quotes(const char *value);
long	ft_atoi_long(char *str, int *error);
char	*ft_init_long(long *sign, char *str);

/* UTILS FUNCTIONS */

void	init_utils(t_utils *utils, t_env *env);
char	*get_value_from_env(t_env *env, char *key);
void	ft_modify_especific_env(char *cwd, t_env *env, char *key_value);
int		ft_find_quotes(char *str);
void	ft_double_quotes(t_utils *utils, char *temp_str, int *i, int *j);
void	ft_single_quotes(char *str_value, char *temp_str, int *i, int *j);
char	*ft_create_new_str(int *i, int *j, t_utils *utils);
int		ft_valid_env(char c);
char	*ft_check_quotes(t_utils *utils);
void	ft_modify_especific_env(char *cwd, t_env *env, char *key_value);
char    *ft_get_path(char *path, char *cmd);
char	*ft_random_filename(void);
void	filename(char *name);

/*          FREE FUNCTIONS         */
void	ft_free_tokens(t_tokens **lexer);
void    ft_free_cmd(t_cmds *cmd);
void    *ft_free_one_to_cmd(t_cmds *cmd);
void    *ft_free_redir(t_dir *node);
void	ft_free_array(char **array);
void	ft_free_utils(t_utils *utils);
void	ft_free_env(t_env *env);


#endif
