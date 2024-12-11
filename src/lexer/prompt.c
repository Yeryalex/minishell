/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/12/01 17:00:08 by rbuitrag         ###   ########.fr       */
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

void	prompt_loop(void)
{
	char		*input;
	t_tokens	*commands;
	t_tokens	*tmp;
	
	input = NULL;
	while (1)
	{
| 	input = read_input();
		if (!input)
		{
			free(input);
			break ;
		}
		commands = ft_lexer_input(input);

  		tmp = commands;
 	 	printf(GREEN "Prompt ejemplo %s\n", input);
 	 	while (tmp)
 		{
      		printf(GRAY "Value: %s, Type: %d\n", tmp->value, tmp->token);
			tmp = tmp->next;
	 	}
		ft_parser(commands);
	}
  	ft_free_tokens(&commands);
  	ft_free_tokens(&tmp);
	free(input);
}
