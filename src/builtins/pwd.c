/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:32:09 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/02/24 11:20:01 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_pwd(t_env *env, int fd)
{
	char	cwd[1024];
	char	*_pwd;

	if (!getcwd(cwd, 1024))
	{
		_pwd = get_value_from_env(env, "PWD");
		ft_putstr_fd(_pwd, fd);
		ft_putstr_fd("\n", fd);
		return (0);
	}
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
	return (0);
}
