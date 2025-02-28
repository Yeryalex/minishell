/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norminette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:07:47 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/28 14:18:39 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_auxiliar_free(t_cmds *cmd, char *input, t_tokens *commands)
{
	ft_free_tokens(&commands);
	ft_free_cmd(cmd);
	free(input);
}

int	is_directory(t_cmds *parser_nodes)
{
	struct stat	path_stat;

	stat(parser_nodes->full_path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parser_nodes->cmd_array[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (1);
	}
	return (0);
}

void	write_error_fd(char *target, char *error, int fd)
{
	ft_putstr_fd(target, fd);
	ft_putstr_fd(error, fd);
}
