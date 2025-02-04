/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:32:09 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/04 17:15:57 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_pwd(t_env *env)
{
	char	cwd[1024];
	char	*PWD;

	if (!getcwd(cwd, 1024))
	{
		PWD = get_value_from_env(env, "PWD");
		printf("%s\n", PWD);
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
