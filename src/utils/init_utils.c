/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:52:14 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/24 10:54:45 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_utils(t_utils *utils, t_env *env)
{
	utils->environ = env;
	utils->next = NULL;
	utils->prev = NULL;
	utils->stdin = 0;
	utils->stdout =	0;
	utils->exit_status = 0;
	utils->builtins[0] = "echo";
	utils->builtins[1] = "cd";
	utils->builtins[2] = "pwd";
	utils->builtins[3] = "export";
	utils->builtins[4] = "unset";
	utils->builtins[5] = "env";
	utils->builtins[6] = "exit";
	utils->builtins[7] = NULL;
}
