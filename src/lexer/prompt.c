/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/28 14:37:41 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*static void	ft_cleanup_loop(t_tokens **commands, t_cmds *cmd, char *input)
{
	if (commands)
		ft_free_tokens(commands);
	if (cmd)
		ft_free_cmd(cmd);
	if (input)
		free(input);
}*/

void	prompt_loop(t_utils *utils, char *path)
{
	char		*input;
	t_tokens	*commands;
	t_cmds	*cmd;
	char **env;
	
	input = NULL;
	env = ft_list_to_char(utils->environ);
	while (1)
	{
 		input = read_input();
		if (!input)
		{
			free(input);
			break ;
		}
		commands = ft_lexer_input(input);
		if (!commands)
        {
            free(input);
            continue;
        }
 	 	cmd = ft_parser(commands, path);
		ft_executor(cmd, utils, env);
    }
  	ft_free_tokens(&commands);
  	free(input);
}
