/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:59:53 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/11/29 08:29:55 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Función para liberar la memoria de los tokens
void	ft_free_tokens(t_tokens **head)
{
	t_tokens	*temp;

	while (head)
	{
		temp = head->next;
		free(head->value);
		free(head);
		head = temp;
	}
	head = NULL;
}

// tengo que revisar el ultimo nodo para guardarlo tambien
int	ft_addlast_node(t_tokens **lexer, t_tokens *current_node)
{
	t_tokens	*tmp_node;

	if (!*lexer)
	{
		*lexer = current_node;
		return (0);
	}
	tmp_node = *lexer;
	while (tmp_node->next)
		tmp_node = tmp_node->next;
	tmp_node->next = current_node;
	//current_node->prev = tmp_node;
	return (0);
}

int	ft_is_metacharacter(int c)
{
	if (!ft_isspace(c) && !ft_strchr("<>|", c))
		return (1);
	return (0);
}

// vamso a controlar la salida de que me falten comillas, 
void	*ft_exit_error(char quote)
{
	ft_putstr_fd("minishell: Error! unclosed quote ", 2);
	ft_putchar_fd(quote, 2);
	ft_putchar_fd('\n', 2);
	return (NULL);
}

// Necesito que recoja el total de chars en word
char	*ft_get_word(char **input)
{
	int		i;
	char	*value;
	char	quote;

	i = 0;
	quote = 0;
	while ((*input)[i] && (ft_is_metacharacter((*input)[i]) || quote != 0))
	{
		if ((*input)[i] == '"' || (*input)[i] == '\'')
		{
			if (quote == 0)
				quote = (*input)[i];
			else if ((*input)[i] == quote)
				quote = 0;
		}
		++i;
	}
	if (quote != 0)
		return (ft_exit_error(quote));
	value = ft_substr(*input, 0, i);
	*input = *input + i;
	return (value);
}

// recogemos el valor para el nodo, ahora necesaroi porque pilla +de 1 caracter version anterior
char	*ft_get_value(char **input)
{
	char	*value;
	int		i;

	i = 0;
	if (ft_strchr("<>|", **input))
	{
		++i;
		if (!ft_strncmp(*input, "<<", 2) || !ft_strncmp(*input, ">>", 2))
			++i;
		value = ft_substr(*input, 0, i);
		*input += i;
	}
	else
		value = ft_get_word(input);
	return (value);
}
