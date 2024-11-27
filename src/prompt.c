/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/11/27 20:10:40 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_ispace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_istoken(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

// Agrega un token al final de la lista doblemente enlazada
void	add_token(t_tokens **head, t_tokens *new_token)
{
	t_tokens	*temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

// Determina el tipo de token basado en un carácter


t_type	determine_type(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (GTHAN);
	else if (c == '<')
		return (STHAN);
	return (WORD);
}

// Crea un nuevo nodo de token
t_tokens	*create_token(const char *value, t_type type)
{
	t_tokens	*new_token;

	new_token = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->token = type;
	new_token->next = NULL;
	return (new_token);
}

t_tokens	*parse_input(const char *input)
{
	const char		*start;
	t_tokens	*head;
	char		*word;
	char		token_char[2];

	head = NULL;

	if (!input)
		return (NULL);
	while(*input)
	{
		while (ft_ispace(*input))
			input++;
		if (*input == '\0')
			break ;
		if (ft_istoken(*input))
		{
			token_char[0] = *input;
			token_char[1] = '\0';
			add_token(&head, create_token(token_char, determine_type(*input)));
			input++;
		}
		else
		{
			start = input;
			while (*input && !ft_ispace(*input) && !ft_istoken(*input))
				input++;
			word = ft_strndup(start, (input + 1 - start));
			if (!word)
				return (NULL);
			add_token(&head, create_token(word, WORD));
			free (word);
		}
	}
	return (head);
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
	
	//input = readline("minishel42~");

	while (1)
	{
		input = read_input();
		if (!input)
			break ;
		commands = parse_input(input);

  	tmp = commands;
 	 printf(GREEN "Prompt ejemplo %s\n", input);
 	 while (tmp)
 	 {
      	printf(GRAY "Value: %s, Type: %d\n", tmp->value, tmp->token);
    	  tmp = tmp->next;
 	 }
  	free_tokens(commands);
	}
/*
		if (commands)
		{
			printf("%s\n", commands->value);
			//execute_commands(commands);
			free_tokens(commands);
		}
		free(input);
	}

	commands = parse_input(input);
	tmp = commands;
	printf(GREEN "Prompt ejemplo %s\n", input);
	while (tmp)
    {
        printf(GRAY "Value: %s, Type: %d\n", tmp->value, tmp->token);
        tmp = tmp->next;
    }
    free_tokens(commands);*/
}
