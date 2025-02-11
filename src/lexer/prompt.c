/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/11 20:22:25 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void ft_cleanup(char **input, t_tokens **commands, t_cmds **cmd)
{
	if (*input)
	{
		free(*input);
		*input = NULL;
	}
	if (*cmd)
	{
		ft_free_cmd(*cmd);
		*cmd = NULL;
	}
	(void)commands;
	/*if (*commands)
	{
		ft_free_tokens(commands);
		*commands = NULL;
	}*/
}

static int	ft_process_input(char *input, t_tokens **commands, t_cmds **cmd, char *path, t_utils *utils)
{
	*commands = ft_lexer_input(input);
	if (!*commands)
		return (0);
	*cmd = ft_parser(*commands, path, utils);
	if (!*cmd)
		return (ft_free_tokens(commands), free(path), 0);
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
		env = NULL;
        return;
    }
	while (g_exit)
	{
		ft_cleanup(&input, &commands, &cmd);
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
			g_exit = 0;
			continue;
		}
		if (!ft_process_input(input, &commands, &cmd, path, utils))
		{
			ft_cleanup(&input, &commands, &cmd);
			g_exit = 0;
			continue;
		}
		else
			ft_executor(cmd, utils, env);
		ft_cleanup(&input, &commands, &cmd);
	}
	rl_clear_history();
	if (env)
		ft_free_array(env);
}