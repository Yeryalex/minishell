/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:26 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 14:31:44 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tokens	*ft_create_node(const char **input, t_utils *utils, t_tokens *lexer)
{
	char		*str_value;
	t_tokens	*new_node;

	new_node = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new_node)
		return (NULL);
	new_node->prev = NULL;
	new_node->next = NULL;
	new_node->token = NONE;
	str_value = ft_get_value(input);
	if (!str_value)
		return (free(new_node), NULL);
	utils->value_to_expand = str_value;
	ft_no_pipe(str_value, new_node);
	if (!ft_check_quotes_hdoc(lexer))
		new_node->value = str_value;
	else
		new_node->value = ft_check_quotes(utils);
	if (!new_node->value)
		return (free(new_node), NULL);
	if (new_node->token == WORD)
		return (new_node);
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

int	ft_check_syntax(t_tokens *lexer, t_type token_type)
{
	t_tokens	*temp;

	temp = lexer;
	while (temp)
	{
		if (temp->token == token_type)
		{
			if (temp->prev && ft_strchr("<>", *temp->value))
			{
				if (temp->token == token_type)
					return (ft_print_syntax_error(temp));
			}
			else if (!temp->next)
			{
				printf("minishell: syntax error near");
				printf(" unexpected token `newline'\n");
				return (0);
			}
		}
		temp = temp->next;
	}
	return (1);
}

t_tokens	*ft_syntax(t_tokens *lexer, t_utils *utils)
{
	if (!ft_check_dot(lexer, utils))
		return (ft_free_tokens(&lexer), NULL);
	if (!ft_check_syntax_pipe(lexer))
	{
		utils->exit_status = 2;
		printf("minishell: syntax error near unexpected token `|'\n");
		return (ft_free_tokens(&lexer), NULL);
	}
	if (!ft_check_syntax(lexer, STHAN) || !ft_check_syntax(lexer, GTHAN)
		|| !ft_check_syntax(lexer, APPEND) || !ft_check_syntax(lexer, H_DOC))
	{
		utils->exit_status = 2;
		utils->redir_error = 1;
		return (ft_free_tokens(&lexer), NULL);
	}
	return (lexer);
}

t_tokens	*ft_lexer_input(const char *input, t_utils *utils)
{
	t_tokens	*node;
	t_tokens	*lexer;

	lexer = NULL;
	if (!input)
		return (NULL);
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		node = ft_create_node(&input, utils, lexer);
		if (!node)
			return (ft_free_tokens(&lexer), NULL);
		if (ft_addlast_node(&lexer, node))
			return (ft_free_in_input(lexer, node));
	}
	if (lexer)
	{
		lexer = ft_check_no_redir(lexer, utils);
		if (lexer)
			return (ft_syntax(lexer, utils));
	}
	return (lexer);
}
