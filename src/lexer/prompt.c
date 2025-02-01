/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/01/31 12:23:52 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*static void	ft_cleanup_loop(t_tokens **commands, t_cmds *cmd, t_utils *utils, char *input, char **env)
{
	if (commands)
		ft_free_tokens(commands);
	if (cmd)
		ft_free_cmd(cmd);
	if (input)
		free(input);
	if (utils)
		ft_free_utils(utils);
	if (env)
		ft_free_array(env);
}*/

void	prompt_loop(t_utils *utils, char *path)
{
	char		*input;
	t_tokens	*commands;
	t_cmds	*cmd;
	char **env;
	
	input = NULL;
	cmd = NULL;
	commands = NULL;
	env = ft_list_to_char(utils->environ);
	while (1)
	{
		input = read_input(env);
		if (!input)
		{
			free(input);
			ft_free_array(env);
			ft_free_utils(utils);
			//ft_cleanup_loop(&commands, cmd, utils, input, env);
			ft_putstr_fd("exit\n", 1);
			exit(EXIT_SUCCESS);
		}
		commands = ft_lexer_input(input);
		if (!commands)
        {
			//ft_free_array(env);
            ft_free_tokens(&commands);
			free(input);
			//ft_free_utils(utils);
			//ft_cleanup_loop(&commands, cmd, utils, input, env);
            continue;
        }
 	 	cmd = ft_parser(commands, path);
		if (!cmd)
		{
			ft_free_tokens(&commands);
			//ft_free_cmd(cmd);
			free(input);
			//ft_cleanup_loop(&commands, cmd, utils, input, env);
			continue;
		}
			ft_free_tokens(&commands);
			ft_executor(cmd, utils, env);
			ft_free_cmd(cmd);
        	free(input);
			//ft_free_array(env);
	}
	rl_clear_history();
	//ft_cleanup_loop(&commands, cmd, utils, input, env);
}
