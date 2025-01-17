/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expanser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:16:01 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/17 11:16:05 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


char *ft_validate_command(char **paths, const char *command)
{
    char *full_path;
    int i = 0;

    while (paths[i])
    {
        full_path = malloc(strlen(paths[i]) + strlen(command) + 2);
        if (!full_path)
            return (NULL);
        strcpy(full_path, paths[i]);
        strcat(full_path, "/");
        strcat(full_path, command);
        if (access(full_path, X_OK) == 0)
            return full_path;
        free(full_path);
        i++;
    }
    return (NULL);
}

/* Lo quitare con el de Yeri es solo pruebas*/
void execute_commands(t_cmds *cmds)
{
    while (cmds)
    {
        if (fork() == 0)
        {
            execve(cmds->cmd_array[0], cmds->cmd_array, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else
            break ;
        cmds = cmds->next;
    }
}
