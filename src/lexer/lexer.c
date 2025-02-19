/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:26 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/28 14:16:29 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tokens *ft_create_node(const char **input)
{
    t_tokens *new_node = (t_tokens *)malloc(sizeof(t_tokens));
    if (!new_node)
        return (NULL);
    new_node->prev = NULL;
	new_node->next = NULL;
	new_node->value = ft_remove_quotes(ft_get_value(input));
    if (!new_node->value)
        return (free(new_node),NULL);
    new_node->token = ft_determine_type(new_node->value);
	return (new_node);
}

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
	current_node->prev = tmp_node;
	return (0);
}

int	ft_check_pipes(t_tokens *lexer)
{
	t_tokens *temp;

	temp = lexer;
	if (!ft_strncmp(temp->value, "|", 1))
			return (0);
	if (!ft_strncmp(temp->value, ">", 1))
		return (-1);
	while (temp)
	{
		if (!ft_strncmp(temp->value, "|", 1) && !temp->next)
			return (0);
		if ((!ft_strncmp(temp->value, ">", 1)) && !temp->next)
			return (-1);
		if ((!ft_strncmp(temp->value, "<", 1)) && !temp->next)
			return (-1);
		temp = temp->next;
	}
	return (1);
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
			input++;
		if (!*input)
			break ;
		node = ft_create_node(&input);
		if (!node)
			return (ft_free_tokens(&lexer), NULL);
		if (ft_addlast_node(&lexer, node))
		{
			ft_free_tokens(&lexer);
			ft_free_tokens(&node);
			return (NULL);
		}
	}
	if (lexer)
	{
		if (!ft_check_pipes(lexer))
		{
			printf("minishell: syntax error near unexpected token > or `|'\n");
			return (ft_free_tokens(&lexer), NULL);
		}
		if (ft_check_pipes(lexer) == -1)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (ft_free_tokens(&lexer), NULL);
		}
	}
	return (lexer);
}
