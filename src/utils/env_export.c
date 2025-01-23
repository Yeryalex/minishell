/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 08:31:54 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/10 12:11:41 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*t_env    *ft_env_init(char **env)
{
    t_env	*env_list;
    t_env	*new;
    int		i;

    i = 0;
    env_list = NULL;
    while (env[i])
    {
        new = (t_env *)malloc(sizeof(t_env));
        if (!new)
        {
            free(new);
            return (NULL);
        }
        new->key = ft_strdup(ft_split(*env, '=')[0]);
        new->value = ft_strdup(ft_split(*env, '=')[1]);
        new->next = env_list;
        env_list = new;
        i++;
    }

    return (env_list);
}
int	ft_print_env(t_env *env_list, int fd)
{
	while (env_list)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(env_list->key, fd);
		if (env_list->exported)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(env_list->value, fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
		env_list = env_list->next;
	}
	return (0);
}*/

void ft_print_env_list(t_env *envs)
{
    while (envs)
    {
        printf("Key: %s\n", envs->key);
        envs = envs->next;
    }
}

void	*ft_print_stderr(char *str)
{
	ft_putstr_fd("mini: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (NULL);
}

char	*ft_get_env_key(char *str)
{
	char	*separator;
	int		i;

	if (!str)
		return (NULL);
	separator = ft_strchr(str, '=');
	i = 0;
	while (str[i] && (str + i) != separator)
	{
		if (i == 0 && (!ft_isalpha(str[i]) && str[i] != '_'))
			return (ft_print_stderr(str));
		if (str[i] == '+' && (str + i + 1) == separator)
		{
			separator -= 1;
			break ;
		}
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (ft_print_stderr(str));
		++i;
	}
	if (separator == str)
		return (ft_print_stderr(str));
	if (!separator)
		return (ft_strdup(str));
	return (ft_substr(str, 0, separator - str));
}

char	*ft_get_env_value(char *key_value)
{
	int	i;

	if (!key_value)
		return (NULL);
	i = 0;
	while (key_value[i])
	{
		if (key_value[i] == '=')
		{
			if (i != 0 && key_value[i - 1] == '+')
				--i;
			break ;
		}
		++i;
	}
	if (!key_value[i])
		return (NULL);
	return (key_value + i);
}
