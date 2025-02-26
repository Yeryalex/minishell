/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:26 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/24 17:52:30 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_no_pipe(char	*str_value, t_tokens *new_node)
{
	int i;

	if (!ft_strncmp(str_value, ">>", 2) || !ft_strncmp(str_value, "<<", 2)
		|| !ft_strncmp(str_value, "||", 2))
		return ;
	if (ft_strlen(str_value) > 1)
	{
		i = 0;
		while (str_value[i])
		{
			if (ft_strchr("<>|", str_value[i]))
			{
				new_node->token = WORD;
				break;
			}
			i++;
		}	
	}
}

t_tokens *ft_create_node(const char **input, t_utils* utils)
{
	char	*str_value;

	t_tokens *new_node = (t_tokens *)malloc(sizeof(t_tokens));
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
 	new_node->value = ft_check_quotes(utils);
	if (!new_node->value)
        return (free(new_node),NULL);
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

int	ft_check_syntax(t_tokens *lexer, char *value, t_type token_type)
{
	t_tokens *temp;
	temp = lexer;
	
	if (!ft_strncmp(value, "|", 1) && !ft_strncmp(temp->value, value, 2) && temp->token == token_type)
			return (0);
	while (temp)
	{
		if (!ft_strncmp(temp->value, value, 2) && !temp->next && temp->token == token_type)
			return (0);
		if (temp->next && temp->next->token != WORD)
		{
			if (!ft_strncmp(temp->value, value, 2) && temp->next->token != token_type)
				return (0);
		}	
		temp = temp->next;
	}
	return (1);
}

t_tokens	*ft_syntax(t_tokens *lexer)
{
	if (!ft_check_syntax(lexer, "|", PIPE))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (ft_free_tokens(&lexer), NULL);
	}
	if (!ft_check_syntax(lexer, ">>", APPEND) || !ft_check_syntax(lexer, "<<", H_DOC)
		|| !ft_check_syntax(lexer, ">", GTHAN) || !ft_check_syntax(lexer, "<", STHAN))
	{
		printf("minishell: syntax error near unexpected token `%s'\n", lexer->value);
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
	while(*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		node = ft_create_node(&input, utils);
		if (!node)
			return (ft_free_tokens(&lexer), NULL);
		if (ft_addlast_node(&lexer, node))
			return(ft_free_tokens(&lexer), ft_free_tokens(&node), NULL);
	}
	 if (lexer)
	 	return (ft_syntax(lexer));
	return (lexer);
}
