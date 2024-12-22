#include "../inc/minishell.h"

t_env    *ft_env_init(char **env)
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