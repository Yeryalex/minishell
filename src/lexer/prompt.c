/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/25 09:04:35 by rbuitrag         ###   ########.fr       */
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
	{
		return (NULL);
		free (new_node);
	}
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

/*
// Este es nuestro lexer el anteriormente llamado parser_input (así ya lo podemos
//  montar y esctuturar mejor)
//  */
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
			return (NULL);
		}
	}
	return (lexer);
}

char	*read_input(void)
{
	char	*input;
	
	input = readline(CYAN "minishell> " RESET);
	if (input && *input)
		add_history(input);
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

/* esta funcion captura de t_env a t_utils environ para usar en todos los procesos como char ** */
char **ft_list_to_char(t_env *env)
{

    char    **char_env;
    int     size;
    char    *key_value;

    size = ft_lstsize(env);
    char_env = (char **)malloc(sizeof(char *) * (size + 1));
    if (!char_env)
        return (NULL);
    while (env)
    {
        key_value = ft_strjoin(ft_strdup(env->key), "=");
        key_value = ft_strjoin(key_value, ft_strdup(env->value));
        *char_env = key_value;

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
            free(input);
            continue;
        }
 	 	cmd = ft_parser(commands, path);
		t_cmds *temp;
		temp = cmd;
		while (temp)
		{
			printf(CYAN "%s\n", temp->cmd_array[0]);
			printf(GRAY "%s\n", temp->full_path);
			temp = temp->next;
		}
		ft_executor(cmd, utils, env);
    }
  	ft_free_tokens(&commands);
  	free(input);
}
