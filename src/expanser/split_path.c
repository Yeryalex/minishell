/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:15:50 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/17 11:15:53 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int count_substrings(const char *str, char delimiter)
{
    int count = 0;
    int in_substring = 0;

    while (*str)
    {
        if (*str != delimiter && !in_substring)
        {
            in_substring = 1;
            count++;
        }
        else if (*str == delimiter)
        {
            in_substring = 0;
        }
        str++;
    }
    return count;
}

static char *substring(const char *start, const char *end)
{
    char *substr = (char *)malloc(end - start + 1);
    if (!substr)
        return NULL;
    strncpy(substr, start, end - start);
    substr[end - start] = '\0';
    return substr;
}

char **ft_split_path(const char *path)
{
    char **result;
    const char *start;
    int i = 0;

    if (!path)
        return NULL;

    result = (char **)malloc((count_substrings(path, ':') + 1) * sizeof(char *));
    if (!result)
        return NULL;

    while (*path)
    {
        while (*path == ':')
            path++;
        start = path;
        while (*path && *path != ':')
            path++;
        if (path != start)
        {
            result[i] = substring(start, path);
            if (!result[i])
            {
                while (i > 0)
                    free(result[--i]);
                free(result);
                return NULL;
            }
            i++;
        }
    }
    result[i] = NULL;
    return result;
}
