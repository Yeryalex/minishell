/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:32:09 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/01/28 10:59:59 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

int	ft_pwd(t_env *env)
{
	char	*pwd;
	
	pwd = (char *)malloc(sizeof(char) + 200);	
	pwd = get_value_from_env(env, "PWD");
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
