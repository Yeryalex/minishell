/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:38 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/02/12 13:15:11 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_handle_exit(char *input)
{
	free(input);
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
}

static int	ft_process_input(char *input, t_tokens **commands, t_cmds **cmd, char *path, t_utils *utils)
{
	*commands = ft_lexer_input(input);
	if (!*commands)
		return (ft_free_tokens(commands), free(input), 0);
	*cmd = ft_parser(*commands, path, utils);
	if (!cmd)
		return (ft_free_tokens(commands), free(input), 0);
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
	while (g_signal)
	{
		if (utils->status == 0)
			break;
		input = read_input(env, utils);
		if (!input)
			ft_handle_exit(input);
		if (!ft_process_input(input, &commands, &cmd, path, utils))
			continue;
		ft_free_tokens(&commands);
		ft_executor(cmd, utils, env);
		ft_free_cmd(cmd);
        free(input);
	}
	ft_free_array(env);
	rl_clear_history();
}