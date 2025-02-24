/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/24 09:30:00 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_handle_exit(t_utils *utils, char *input, char **env)
{
	free(input);
	ft_free_array(env);
	ft_free_utils(utils);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}

static int	ft_process_input(char *input, t_tokens **commands, t_cmds **cmd, t_utils *utils)
{
	char	*path;

	path = NULL;
	path = ft_get_paths_from_env(utils->environ);
	*commands = ft_lexer_input(input, utils);
	if (!*commands)
		return (ft_free_tokens(commands), free(input), 0);
	*cmd = ft_parser(*commands, path, utils);
	if (!cmd)
		return (ft_free_tokens(commands), free(input), 0);
	return (1);
}

void	prompt_loop(t_utils *utils)
{
	char		*input;
	t_tokens	*commands;
	t_cmds		*cmd;
	char		**env;

	input = NULL;
	cmd = NULL;
	commands = NULL;
	ft_control_c(utils);
	env = ft_list_to_char(utils->environ);
	while (1)
	{
		ft_init_signals(0);
		if (utils->status == 0)
			break;
		input = read_input(env, utils);
		if (!input)
			ft_handle_exit(utils, input, env);
		if (!ft_process_input(input, &commands, &cmd, utils))
		{
			utils->exit_status = 2;
			continue;
		}
		ft_free_tokens(&commands);
		ft_executor(cmd, utils, env);
		ft_free_cmd(cmd);
        free(input);
		utils->cmds_amount++;
	}
	ft_free_array(env);
	rl_clear_history();
}

