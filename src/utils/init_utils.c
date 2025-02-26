/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:52:14 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/26 17:41:49 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_utils(t_utils *utils, t_env *env)
{
	utils->environ = env;
	utils->status = -1;
	utils->next = NULL;
	utils->prev = NULL;
	utils->stdin = 0;
	utils->stdout = 0;
	utils->exit_status = 0;
	utils->cmds_amount = 0;
	utils->redir_error = 0;
	utils->builtins[0] = "echo";
	utils->builtins[1] = "cd";
	utils->builtins[2] = "pwd";
	utils->builtins[3] = "export";
	utils->builtins[4] = "unset";
	utils->builtins[5] = "env";
	utils->builtins[6] = "exit";
	utils->builtins[7] = NULL;
}

void	ft_free_cmd(t_cmds *cmd)
{
	t_cmds	*tmp;

	if (!cmd)
		return ;
	while (cmd)
	{
		tmp = cmd->next;
		ft_free_one_to_cmd(cmd);
		cmd = tmp;
	}
}
