/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:59:53 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/28 14:49:12 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
// Función para liberar la memoria de los tokens
*/
void	ft_free_tokens(t_tokens **head)
{
	t_tokens	*temp;

	while (*head)
	{
		temp = (*head)->next;
		free((*head)->value);
		free((void*)(*head)->token);
		free(*head);
		*head = temp;
	}
	*head = NULL;
}

int	ft_is_metacharacter(int c)
{
	if (!ft_isspace(c) && !ft_strchr("<>|", c))
		return (1);
	return (0);
}

/*
// vamos a controlar la salida si le faltan comillas,
*/ 
void	*ft_exit_error(char quote)
{
	ft_putstr_fd("minishell: Error! unclosed quote ", 2);
	ft_putchar_fd(quote, 2);
	ft_putchar_fd('\n', 2);
	return (NULL);
}

// Valida que las comillas sean pares y estén correctamente cerradas
static int	ft_validate_quotes(const char *value)
{
	char	quote_type;
	int		i;
	int		opened;

	i = 0;
	opened = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '"')
		{
			quote_type = value[i];
			opened++;
			i++;
			while (value[i] && value[i] != quote_type)
				i++;
			if (value[i] == quote_type)
				opened--;
		}
		if (value[i])
			i++;
	}
	// Si no se cerraron correctamente las comillas
	if (opened > 0)
	{
		printf("Unexpected close quote\n");
		return (0);
	}
	return (1);
}

char	*ft_remove_quotes(const char *value)
{
	char	*trimmed;
	char	*result;

	if (!value)
		return (NULL);

	// Validar las comillas primero
	if (!ft_validate_quotes(value))
		return (NULL);

	// Trim comillas simples y dobles
	trimmed = ft_strtrim(value, "\'\"");
	if (!trimmed)
		return (NULL);

	// Duplicar el valor sin las comillas
	result = ft_strdup(trimmed);
	free(trimmed);
	return (result);
}

void	ft_skip_spaces_and_quotes(char **input)
{
	char	quote_type;

	while (**input && ft_isspace(**input))
		(*input)++;
	if (**input == '\'' || **input == '"')
	{
		quote_type = **input;
		(*input)++;
		while (**input && **input != quote_type)
			(*input)++;
		if (**input == quote_type)
			(*input)++;
	}
}
