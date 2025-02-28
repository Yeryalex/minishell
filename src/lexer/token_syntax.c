/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:30:49 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/28 14:18:54 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_no_pipe(char	*str_value, t_tokens *new_node)
{
	int	i;

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
				break ;
			}
			i++;
		}
	}
}

int	ft_check_quotes_hdoc(t_tokens *lexer)
{
	t_tokens	*tmp;

	tmp = lexer;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!ft_strncmp(tmp->value, "<<", 3))
			return (0);
	}
	return (1);
}

t_tokens	*ft_check_no_redir(t_tokens *lexer, t_utils *utils)
{
	t_tokens	*temp;

	temp = lexer;
	while (temp)
	{
		if (temp->next)
		{
			if ((temp->token == GTHAN || temp->token == APPEND
					|| temp->token == STHAN)
				&& !ft_strncmp("", temp->next->value, 1))
			{
				printf("Minishell: ambiguous redirect\n");
				utils->exit_status = 1;
				return (ft_free_tokens(&lexer), NULL);
			}
		}
		temp = temp->next;
	}
	return (lexer);
}

int	ft_check_syntax_pipe(t_tokens *lexer)
{
	t_tokens	*temp;

	temp = lexer;
	if (temp->token == PIPE)
		return (0);
	while (temp)
	{
		if (temp->prev)
		{
			if (temp->prev->token == PIPE && temp->token == PIPE)
				return (0);
		}
		if (!temp->next && temp->token == PIPE)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	ft_check_dot(t_tokens *lexer, t_utils *utils)
{
	struct stat	path_stat;

	if (stat(lexer->value, &path_stat) == 0)
	{
		if (!ft_strncmp(lexer->value, ".", 2)
			&& !lexer->value[1] && !lexer->next)
		{
			utils->exit_status = 2;
			printf("Minishell: .: filename argument required\n");
			return (0);
		}
	}
	if (!ft_strncmp(lexer->value, "minishell", 10))
	{
		printf("minishell: command not found\n");
		utils->exit_status = 127;
		return (0);
	}
	return (1);
}
