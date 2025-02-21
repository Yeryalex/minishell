/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:31:20 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/21 09:08:51 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

static int	ft_create_new_str(char *str, int i, char *quote, char **tmp)
{
	*quote = str[i];
	if (!*tmp)
	{
		*tmp = (char *)ft_calloc(sizeof(char), ft_strlen(str) - 1);
		if (!*tmp)
			return (1);
		if (i != 0)
			ft_strlcat(*tmp, str, i + 1);
	}
	return (0);
}

char	*ft_remove_quotes(char *str)
{
	char	*tmp;
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	tmp = NULL;
	while (str && str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == 0)
		{
			if (ft_create_new_str(str, i, &quote, &tmp))
				return (NULL);
			++i;
			continue ;
		}
		if (tmp && str[i] != quote)
			ft_strlcat(tmp, str + i, ft_strlen(tmp) + 2);
		if (str[i] == quote)
			quote = 0;
		++i;
	}
	if (tmp)
		return (tmp);
	return (str);
}

int	ft_remove_parser_quotes(t_cmds *cmd)
{
	int		i;
	char	*tmp;

	while (cmd)
	{
		i = 0;
		while (cmd->cmd_array && cmd->cmd_array[i])
		{
			tmp = ft_remove_quotes(cmd->cmd_array[i]);
			if (tmp && tmp != cmd->cmd_array[i])
			{
				free (cmd->cmd_array[i]);
				cmd->cmd_array[i] = tmp;
			}
			else if (!tmp)
				return (-1);
			++i;
		}
		cmd = cmd->next;
	}
	return (0);
}
