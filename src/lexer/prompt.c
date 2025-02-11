/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/11 10:09:52 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static void ft_cleanup(char *input, t_tokens *commands, t_cmds *cmd)
{
	if (input)
		free(input);
	if (cmd)
		ft_free_cmd(cmd);
	if (commands)
		ft_free_tokens(&commands);
	input = NULL;
    cmd = NULL;
    commands = NULL;
}

static int	ft_process_input(char *input, t_tokens **commands, t_cmds **cmd, char *path, t_utils *utils)
{
	*commands = ft_lexer_input(input);
	if (!*commands)
		return (0);
	*cmd = ft_parser(*commands, path, utils);
	if (!*cmd)
		return (ft_free_tokens(commands), 0);
	return (1);
}


void	prompt_loop(t_utils *utils, char *path)
{
	char		*input;
	t_tokens	*commands;
	t_cmds		*cmd;
	char		**env;

	input = NULL;
	cmd = NULL;
	commands = NULL;
	env = ft_list_to_char(utils->environ);
	if (!env)
    {
        fprintf(stderr, "minishell: error: No tables in env array\n");
		ft_free_array(env);
        return;
    }
	while (g_exit)
	{
		if (utils->status == 0)
		{
			if (env)
			{
				ft_free_array(env);
				env = NULL;
			}
			break;
		}
		ft_init_signals(&utils->mirror_termios);
		input = read_input(env);
		if (input == NULL)
				break;
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		if (!ft_process_input(input, &commands, &cmd, path, utils))
		{
			free(input);
            ft_free_tokens(&commands);
            continue;
		}
		else
		//if (cmd && env)
			ft_executor(cmd, utils, env);
		ft_cleanup(input, commands, cmd);
	}
	ft_clear_lstenv(utils->environ);
	rl_clear_history();
}