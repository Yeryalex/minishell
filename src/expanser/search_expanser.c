/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_expanser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:22:03 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/27 15:22:32 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_extract_env(char *str)
{
	int		i;

	if (!str)
		return (NULL);
	i = 1;
	if (ft_strchr("$?", str[i]))
		return (ft_substr(str, 0, 2));
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (NULL);
	while (str[i] && (ft_isalnum(str[i]) || ft_strchr("_", str[i])))
		++i;
	return (ft_substr(str, 0, i));
}

static t_env	*ft_check_match(char *env, int env_len, t_env *env_list)
{
	while (env_list)
	{
		if (!ft_strncmp(env + 1, env_list->key, env_len))
			break ;
		env_list = env_list->next;
	}
	if (env_list)
		return (env_list);
	return (NULL);
}

t_exp	*ft_get_exp_node(char *env, int exit_status)
{
	t_exp	*new_node;

	new_node = (t_exp *)malloc(sizeof(t_exp));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->old_value = ft_strdup(env);
	if (!ft_strncmp(env, "$?", 3))
		new_node->new_value = ft_itoa(exit_status);
	else if (!ft_strncmp(env, "$$", 3))
		new_node->new_value = ft_itoa(get_pid());
	return (new_node);
}

int	ft_search_expand(char *str, t_env *env_list, int exit_status, t_exp **new)
{
	t_env	*match_node;
	char	*env;
	int		env_len;

	env = ft_extract_env(str);
	if (!env)
		return (-1);
	env_len = ft_strlen(env);
	if (env_len == 1)
	{
		free (env);
		return (0);
	}
	match_node = ft_check_match(env, env_len, env_list);
	if (match_node)
		*new = ft_build_exp_node(env, match_node);
	else if (!ft_strncmp(env, "$?", env_len) || !ft_strncmp(env, "$$", env_len))
		*new = ft_get_exp_node(env, exit_status);
	else if (env_len)
		*new = ft_build_exp_node(env, NULL);
	free (env);
	if (!new)
		return (-1);
	return (env_len - 1);
}

t_exp	*ft_scan_expansions(char *str, t_env *env_list, int exit_status)
{
	t_exp	*expand_nodes;
	t_exp	*new_node;
	char	quote;
	int		env_len;

	if (!str)
		return (NULL);
	quote = 0;
	new_node = NULL;
	expand_nodes = NULL;
	while (*str)
	{
		quote = ft_update_quote_state(*str, quote);
		if (*str == '$' && quote != '\'')
		{
			env_len = ft_search_expand(str, env_list, exit_status, &new_node);
			if (env_len == -1)
				return (ft_free_all_expand_nodes(expand_nodes));
			str += env_len;
			if (new_node)
				ft_norm_and_add(&expand_nodes, new_node, quote);
		}
		++str;
	}
	return (expand_nodes);
}
