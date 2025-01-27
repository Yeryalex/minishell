/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/27 21:44:05 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/*
// Determina el tipo de token basado en un carácter
//  (ok revisado dejar funcionando)
*/
t_type	ft_determine_type(char *value)
{
	if (!ft_strncmp(value, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(value, ">", 1))
	{
		if (!ft_strncmp(value, ">>", 2))
			return (APPEND);
		return (GTHAN);
	}
	else if (!ft_strncmp(value, "<", 1))
	{
		if (!ft_strncmp(value, "<<", 2))
			return (H_DOC);
		return (STHAN);
	}
	else
		return (WORD);
}

/*
// Crea un nuevo nodo de token (create node para que valga para todo
//  es redudante crear token y nodos es lo mismo
*/  
t_tokens	*ft_create_node(const char **input)
{
	t_tokens	*new_node;

	new_node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_node)
		return (ft_free_tokens(&new_node), NULL);
	new_node->value = ft_get_value(input);
	if (!new_node->value)
	{
		free(new_node);
		return (NULL);
	}
	new_node->token = ft_determine_type(new_node->value);
	new_node->next = NULL;
	return (new_node);
}

t_tokens	*ft_lexer_input(const char *input)
{
	t_tokens	*node;
	t_tokens	*lexer;
	
	lexer = NULL;

	if (!input)
		return (NULL);
	while(*input)
	{
		while (ft_isspace(*input))
		{
			input++;
			continue ;
		}
		node = ft_create_node(&input);
		if (!node || (node && ft_addlast_node(&lexer, node)))
		{
			ft_free_tokens(&lexer);
			ft_free_tokens(&node);
			return (NULL);
		}
	}
	//ft_free_tokens(&node);
	return (lexer);
}

char	*read_input(void)
{
	char	*input;
	
	input = readline(CYAN "minishell~> " RESET);
	if (input && *input)
		add_history(input);
		else
			ft_putstr_fd("exit\n", 1);
	return (input);
}

static int ft_lstsize(t_env *env)
{
    int size = 0;

    while (env)
    {
        size++;
        env = env->next;
    }
    return size;
}

/* esta funcion captura de t_env a t_utils ** */
char **ft_list_to_char(t_env *env)
{
    char    **char_env;
    int     size;
    char    *key_value;
	char	*dup_key;
	char	*dup_value;
	char	*temp;

    size = ft_lstsize(env);
    char_env = (char **)malloc(sizeof(char *) * (size + 1));
    if (!char_env)
	{
		ft_free_array(char_env);
        return (NULL);
	}
	while (env)
    {
		dup_key = ft_strdup(env->key);
		dup_value = ft_strdup(env->value);
        key_value = ft_strjoin(dup_key, "=");
       	if (!key_value)
			return (NULL);
		temp = ft_strjoin(key_value, dup_value);
		free(key_value);
		free(dup_key);
		free(dup_value);
        *char_env = temp;
		free(temp);
        char_env++;
        env = env->next;
    }
    return (char_env - size);
}

void	prompt_loop(t_utils *utils, char *path)
{
	char		*input;
	t_tokens	*commands;
	t_cmds	*cmd;
	char **env;
	
	input = NULL;
	env = ft_list_to_char(utils->environ);
	while (1)
	{
 		input = read_input();
		if (!input)
		{
			free(input);
			break ;
		}
		commands = ft_lexer_input(input);
		if (!commands)
        {
            ft_free_tokens(&commands);
            continue;
        }
 	 	cmd = ft_parser(commands, path);
		ft_executor(cmd, utils, env);
    }
  	  	free(input);
		ft_free_cmd(cmd);
		ft_free_tokens(&commands);
}
